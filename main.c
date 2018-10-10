#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>
#include "structures.h"

int main(int argc, char *argv[]) {

    if (argc == 1 || argc < 4) {
        int choice;
        do {
            aboutTuring();
            printf("Press 1 if you want to see the the structure of the input file<Description>\n"
                   "Press 2 if you want to see the the structure of the input file <Tape>\n"
                   "Press 3 if you want exit\n");
            int err = scanf("%d", &choice);
            if (err != 1 || choice < 1 || choice >3) {
                printf("Wrong choise.\n");
                fflush(stdin);
            }
            switch (choice) {
                case 1:
                    aboutDescription();
                    break;
                case 2:
                    aboutTape();
                    break;
                default:
                    break;
            }
        } while (choice != 3);

        exit(0);
    }

    char *descriptionFile, *outputFile, *tapeFile;
    char *modeFlag = NULL;
    int reqSteps = 0, numOfStep = 0;
    struct listOfTapes *tapes = NULL;
    struct listOfStates *states = NULL;
    char voidSymbol = '_';

    char *transition = NULL;

    int curState, numOfTapes;

    struct state *curStateCell = NULL;

    descriptionFile = argv[1];
    tapeFile = argv[2];
    outputFile = argv[3];
    modeFlag = argv[4];

    //читаем файл входных инструкций
    states = readDescription(descriptionFile, states, &curState, &numOfTapes);
    //читаем файл со входной лентой
    tapes = readTapes(tapeFile, tapes, voidSymbol, numOfTapes);

    while(curState != 0){
        if (modeFlag != NULL) {
            if (strcmp(modeFlag, "-d") != 0) {
                printf("Error 1 : Wrong flag.\n");
                exit(1);
            }

            if (strcmp(modeFlag, "-d") == 0 && reqSteps == 0) {
                int choice;
                int err;
                do {
                    printIssues();
                    err = scanf("%d", &choice);
                    if (err != 1 || choice <1 || choice > 6) {
                        printf("Wrong choice.\n");
                        fflush(stdin);
                    }
                    switch (choice) {
                        case 1:
                            break;
                        case 2:
                            printf("Enter number of required steps.\n");
                            err = scanf("%d", &reqSteps);
                            if (err != 1) {
                                printf("Wrong number of steps.\n");
                                fflush(stdin);
                            }
                            if (reqSteps != 0) choice = 1;
                            break;
                        case 3:
                            printTapes(tapes, transition);
                            break;
                        case 4:
                            printCurState(tapes, numOfStep, curState);
                            break;
                        case 5:
                            foutCondition(outputFile, tapes, numOfStep, transition);
                            printf("Done.\n");
                            break;
                        default:
                            exit(0);
                    }
                } while (choice != 1);
            }
        }
        if (reqSteps > 0) reqSteps--;
        step(tapes, states, voidSymbol, numOfStep, &curState, curStateCell, &transition);
        printTapes(tapes, transition);
        numOfStep ++;
    }

    int choice = 0;
    while (choice != 1) {
        printFinalIssues();
        int err = scanf("%d", &choice);
        if (err != 1 || choice < 1 || choice > 4) {
            printf("Wrong mode.\n");
            fflush(stdin);
        }
        switch (choice){
            case 1:
                break;
            case 2:
                printTapes(tapes, transition);
                break;
            case 3:
                printCurState(tapes, numOfStep, curState);
                break;
            default:
                foutCondition(outputFile, tapes, numOfStep, transition);
                printf("Done.\n");
                break;
        }
    }

    return 0;
}