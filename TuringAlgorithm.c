#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "structures.h"

/*
 * ищем подходящее нам по номеру состояние в общей структуре состояний
 * ищем подходящую по начальным символам часть состояния в данном состоянии
 * проходим по струтурам tapeCell  поиске символа под кареткой
 * меняем текущий символ в tapeCell на новый
 * в зависимости от параметров состояния, делаем шаг влево, вправо или остаёмся на месте
 *
 * аргументы
 * * tapes - структура лент
 * * states - структура состояний
 * * voidSymbol - пустой символ
 * * numOfStep - номер шага
 * * curStateCell - текущая ячейка ленты
 * * transition - текущее состояние перехода
 */
//struct state *curStateCell = NULL;
//!!!!!!!!!!!!
void step(
        struct listOfTapes *tapes, //
                struct listOfStates *states,
                        char voidSymbol, int numOfStep, int *curState, struct state *curStateCell, char** transition) {
    numOfStep++;

    //находим состояние
    struct listOfStates *curListOfStatesCell = states;
    while (curListOfStatesCell != NULL && curListOfStatesCell->stateNumb != *curState) curListOfStatesCell = curListOfStatesCell->nextState;
    if(curListOfStatesCell == NULL) {
        printf("Error 13 : No suitable state on step num.%i.\n", numOfStep);
        exit(13);
    }

    //ищем подходящую часть состояния
    curStateCell = curListOfStatesCell->thisState;
    while (curStateCell != NULL) {
        char *curCondition = strdup(curStateCell->curCondition);
        curCondition = strtok(curCondition, ",");
        struct listOfTapes *curListOfTapesCell = tapes;

        //сравнение condition с tapes
        while (curListOfTapesCell != NULL) {
            if (curCondition == NULL) {
                printf("Error 9 : Less curCondition on step num.%i", numOfStep);
                exit(9);
            }
            if (curListOfTapesCell->curSymbol != *curCondition) break;

            curListOfTapesCell = curListOfTapesCell->nextTape;
            curCondition = strtok(NULL, ",");
        }

        if (curListOfTapesCell == NULL) break;

        curStateCell = curStateCell->next;
        free(curCondition);
    }


    if (curStateCell == NULL) {
        printf("Error 10 : No suitable state condition no step num.%i.", numOfStep);
        exit(10);
    }

    *transition = (*transition == NULL) ? strdup(curStateCell->curCondition) : curStateCell ->curCondition;
    strcat(*transition, "->");


    char *nextCondition = strdup(curStateCell->newCondition);
    strcat(*transition, nextCondition);
    struct listOfTapes *curListOfTapesCell = tapes;
    while (curListOfTapesCell != NULL) {
        //доходим до положения каретки
        struct tapeCell *curTapeCell = curListOfTapesCell->thisTape;
        while (curListOfTapesCell->curPosition != curTapeCell->position) curTapeCell = curTapeCell->next;

        char *newData = strdup(nextCondition);
        newData = strtok(newData, ",");
        curTapeCell->data = *newData;
        nextCondition = strcut(nextCondition, 2, strlen(nextCondition));

        char *stepDir = strdup(nextCondition);
        stepDir = strtok(stepDir, ";");
        nextCondition = strcut(nextCondition, 2, strlen(nextCondition));
        switch (*stepDir) {
            case 'L':
                if (curTapeCell->prev != NULL) {
                    curListOfTapesCell->curPosition = curTapeCell->prev->position;
                    curListOfTapesCell->curSymbol = curTapeCell->prev->data;
                } else {
                    printf("Error 11 : Can't make left step on step num.%i", numOfStep);
                    exit(11);
                }
                break;
            case 'R':
                if (curTapeCell->next == NULL) {
                    struct tapeCell *newTapeCell = (struct tapeCell *) malloc(sizeof(*newTapeCell));
                    if (newTapeCell == NULL) {
                        printf ("Error 16: Not enough memory.\n");
                        exit(16);
                    }
                    newTapeCell->next = NULL;
                    newTapeCell->data = voidSymbol;
                    newTapeCell->prev = curTapeCell;
                    newTapeCell->position = curTapeCell->position + 1;
                    curTapeCell->next = newTapeCell;
                }
                curListOfTapesCell->curPosition = curTapeCell->next->position;
                curListOfTapesCell->curSymbol = curTapeCell->next->data;
                break;
            default:
                if (*stepDir != 'S') {
                    printf("Error 12 : Wrong step condition in step num.%i.", numOfStep);
                    exit(12);
                }
                curListOfTapesCell->curSymbol = curTapeCell->data;
                break;
        }

        curListOfTapesCell = curListOfTapesCell->nextTape;

        free(newData);
        free(stepDir);
    }

    *curState = curStateCell->nextState;
    free(nextCondition);
    free(transition);
}


