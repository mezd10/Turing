#include <stdio.h>
#include <mem.h>
#include "structures.h"

void aboutTuring() {
    printf("Author: Nikolay Kholkin \n "
           "\tThis is the a Turing machine simulator for several tapes \n"
           "\tIn order for the program to work correctly you need to read the terms of reference \n"
           "\tYou should enter the input data correctly, namely: \n\n"
           "\tFor example: progr.exe description.txt tape.txt out.txt -d \n\n"
           "\tdescription.txt - it is description file, which includes:\n"
           "\ttape.txt        - it is a file with input tapes \n"
           "\tout.txt         - it is output file, where the result of the program is recorded \n"
           "\t-d              - flag indicating debug \n");

}

void aboutDescription() {
    printf("Requirement for input file <Description>:\n"
           "\tNumber of tapes\n"
           "\tAlfabet\n"
           "\tInitial state\n"
           "\tAll other lines are for entering commands\n"
           "\tFor example: q1: _,1,0->_,R;_,R;_,R->q2; 1,1,0->0,R;0,R;0,R;->q2;\n"
           "\t             q2: 1,_,_->1,R;1,R;1,R->q3; 0,_,_->0,R;0,R;0,R;->q2; _,_,_->_,R;_,R;_,R;->q3; 1,1,_->_,R;_,R;_,R;->q3;\n"
           "\t             q3: 1,1,1->1,L;0,L;1,L->q3; 0,1,1->0,S;1,S;0,S;->q0; _,_,_->_,R;_,R;_,R;->q0; _,1,1->_,S;0,S;0,S;->q0;\n");
}

void aboutTape() {
    printf("Requirement for input file <Tape>:\n"
           "First you need to write a tape number, then specify the position of the carriage, and then write the tape itself\n"
           "\tExample:\n"
           "\t         tape1:\n"
           "\t         .....!..\n"
           "\t         _101011_\n"
           "\t         tape2:\n"
           "\t         ..!.....\n"
           "\t         1_11111_\n"
           "\t         tape3: \n"
           "\t         !.......\n"
           "\t         0_11000_\n");
}

void printFinalIssues(){
    printf("The program is finished. Select one of the options:\n");
    printf("1) Exit.\n");
    printf("2) Display taps to the console.\n");
    printf("3) Display the current state of machine to the console (tape number, current symbol, current position).\n");
    printf("4) Output the current state of the machine to the file.\n");
}

void printIssues(){
    printf("Select one of the options:\n");
    printf("1) Make step.\n");
    printf("2) Make a certain number of steps.\n");
    printf("3) Display taps to the console.\n");
    printf("4) Display the current state of machine to the console (tape number, current symbol, current position).\n");
    printf("5) Output the current state of the machine to the file.\n");
    printf("6) Exit debug mode.\n");
}

void printCurState(struct listOfTapes *tapes, int numOfStep, int curState) {
    printf("----------------------\n");
    printf("Step num.%i\n", numOfStep);
    printf("Current state: q%i\n", curState);
    printf("Tapes:\n");

    struct listOfTapes *curListOfTapesCell = tapes;
    while (curListOfTapesCell != NULL) {
        printf("    Tape num.%i: symbol: %c, position: %i.\n", curListOfTapesCell->tapeNumb, curListOfTapesCell->curSymbol, curListOfTapesCell->curPosition);
        curListOfTapesCell = curListOfTapesCell->nextTape;
    }

    printf("----------------------\n");
}

void printTapes(struct listOfTapes *tapes, char* transition) {
    printf("----------------------\n");
    struct listOfTapes *curListOfTapesCell = tapes;

    char *curStates = NULL;
    char *nextStates = NULL;
    char *pereTransition = strdup(transition);

    if (pereTransition != NULL) {
        curStates = strtok(pereTransition, "->");
        nextStates = strtok(NULL, "->");
    }


    while (curListOfTapesCell != NULL) {
        printf("Tape num.%i:\n\t", curListOfTapesCell->tapeNumb);

        if (pereTransition != NULL) {
            printf("%c -> %c, %c; \n \t", curStates[0], nextStates[0], nextStates[2]);
            curStates = strcut(curStates, 2, strlen(curStates) + 1);
            nextStates = strcut(nextStates, 4, strlen(nextStates) + 1);
        }

        struct tapeCell *curTapeCell = curListOfTapesCell->thisTape;

        while (curTapeCell != NULL) {
            if (curTapeCell->position == curListOfTapesCell->curPosition) {
                printf("!");
            }
            else {
                printf(".");
            }
            curTapeCell = curTapeCell->next;
        }

        printf("\n");
        printf("\t");

        curTapeCell = curListOfTapesCell->thisTape;
        while (curTapeCell != NULL) {
            printf("%c", curTapeCell->data);

            curTapeCell = curTapeCell->next;
        }
        printf("\n");
        curListOfTapesCell = curListOfTapesCell->nextTape;
    }

    printf("----------------------\n");
}

