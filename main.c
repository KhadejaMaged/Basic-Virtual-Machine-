#include <stdio.h>
#include <stdbool.h>

bool running = true;
int ip = 0;
int sp = -1;

typedef enum {
    A, B, C, D, E, F,
    NUM_OF_REGISTERS
} Registers;

int stack[256];
int registers[NUM_OF_REGISTERS];

typedef enum {
    PSH,
    ADD,
    SUB,
    MUL,
    DIV,
    POP,
    SET,
    MOV,
    HLT
} InstructionSet;

const int program[] = {
        SET, A, 5,
        SET, B, 6,
        PSH, A,
        PSH, B,
        ADD,
        SET , C , 5 ,
        SET , D , 9 ,
        PSH , C ,
        PSH , D ,
        MUL ,
        SET , E , 10,
        SET , F , 2 ,
        PSH , E ,
        PSH , F ,
        DIV,
        SET , A ,20
        ,SET, B , 25,
        PSH , B,
        PSH,  A,
        SUB,
        MOV, A,
        POP,
        HLT
};


int fetch() {
    return program[ip];
}


bool checkfull() {
    if(sp >= 255) {
        printf("Stack overflow\n");
        return true;
    }
    return false;
}


bool checkempty() {
    if(sp < 0) {
        return true;
    }
    return false;

}


void exp(InstructionSet s) {
    if(checkempty()) {
        printf("Stack is Empty\n");
        return;
    }
    int a = stack[sp];
    sp--;
    int b = stack[sp];
    switch (s) {
        case ADD:
            stack[sp] = b + a;
            printf("%d ADDITION SUCCESSFULLY\n", stack[sp]);
            break;
        case SUB:
            stack[sp] = b - a;
            printf("%d SUBTRACTION SUCCESSFULLY\n", stack[sp]);
            break;
        case MUL:
            stack[sp] = b * a;
            printf("%d MULTIPLICATION SUCCESSFULLY\n", stack[sp]);
            break;
        case DIV:
            stack[sp] = b / a;
            printf("%d DIVISION SUCCESSFULLY\n", stack[sp]);
            break;
        default:
            printf("Choose operand not found\n");
    }
}


void push(){
    if(checkfull()) {
        printf("Stack is full\n");
    } else {
        int reg = program[++ip];
        sp++;
        stack[sp] = registers[reg];
    }
}


void Pop(){
    if(checkempty()) {
        printf("Stack is empty\n");
    } else {
        int val_popped = stack[sp--];
        printf("popped %d\n", val_popped);
    }
}


void set(){
    int reg = program[++ip];
    int value = program[++ip];
    registers[reg] = value;
}

void Move(){
    int reg = program[++ip];
    sp++;
    stack[sp] = registers[reg];
}
void eval(int instr) {
    switch (instr) {
        case HLT: running = false; printf("Done\n"); break;
        case PSH: push();      break;
        case POP: Pop();       break;
        case ADD: exp(ADD);  break;
        case SUB: exp(SUB);  break;
        case MUL: exp(MUL);  break;
        case DIV: exp(DIV);  break;
        case SET: set();        break;
        case MOV:  Move();      break;
        default:    printf("Unknown instruction %d\n", instr);
    }
}

int main() {
    while (running) {
        eval(fetch());
        ip++;
    }
    return 0;
}
