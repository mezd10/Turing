#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "structures.h"

/*Считываем файл Tape
 *создаём заданное количество лент с единственным символом (пустым)
 * поочерёдно заполняем ленты
 * * считываем строчку, выделяем из неё номер ленты, находим нужною ленту в списке созданных
 * * считываем следующую строчку, определяем положение каретки
 * * считываем строчку с лентой, вносим ленту в нашу структуру
 *
 * аргументы:
 * * fileName - имя файла с входными лентами
 * * tapes - структура лент
 * * voidSymbol - пустой символ
 * * numOfTapes - количество лент
*/
struct listOfTapes* readTapes(char *fileName, struct listOfTapes *tapes, char voidSymbol, int numOfTapes) {

    FILE *input;
    input = fopen(fileName, "r");
    if (input == NULL) {
        printf("Error 5 : File \"%s\" can't be open.\n", fileName);
        exit(5);
    }

    //создаём ленты с еиднственным (пустым) символом
    for (int i = 0; i < numOfTapes ; ++i) {
        //создаём пустую ленту с одним пустым символом
        struct listOfTapes *newListOfTapesCell = (struct listOfTapes*)malloc(sizeof(*newListOfTapesCell));
        struct tapeCell *newTapeCell = (struct tapeCell*)malloc(sizeof(*newTapeCell));
        if (newListOfTapesCell == NULL || newTapeCell == NULL) {
            printf("Error 16: Not enough memory.\n");
            exit(16);
        }
        newTapeCell->data = voidSymbol;
        newTapeCell->next = NULL;
        newTapeCell->prev = NULL;
        newTapeCell->position = 1;
        newListOfTapesCell->thisTape = newTapeCell;
        newListOfTapesCell->curSymbol = newTapeCell->data;
        newListOfTapesCell->curPosition = newTapeCell->position;
        newListOfTapesCell->nextTape = NULL;

        //вставляем новую ленту в ленты
        struct listOfTapes *curListOfTapes = tapes;
        if (curListOfTapes == NULL){
            newListOfTapesCell->tapeNumb = 1;
            tapes = newListOfTapesCell;
        }
        else{
            while (curListOfTapes->nextTape != NULL) curListOfTapes = curListOfTapes->nextTape;
            newListOfTapesCell->tapeNumb = (curListOfTapes->tapeNumb +1);
            curListOfTapes->nextTape = newListOfTapesCell;
        }
    }
    //читаем состояния
    char tape[2000000];
    while(fgets(tape, sizeof(tape), input)){
        char *tapePart = tape;
        tapePart = strcut(tapePart, 4, strlen(tapePart) - 2);
        int tapeNum = atoi(tapePart);
        if (tapeNum == 0) {
            printf("Error 6 : Wrong tape number: %s.\n", tapePart);//exit добавить в принт
            exit(6);
        }

        //находим нужную ленту
        struct listOfTapes *curListOfTapesCell = tapes;
        while(curListOfTapesCell != NULL && curListOfTapesCell->tapeNumb != tapeNum) curListOfTapesCell = curListOfTapesCell->nextTape;
        if (curListOfTapesCell == NULL){
            printf("Error 7 : Error: total tapes: %i, required tape: %i.\n", numOfTapes, tapeNum);
            exit(7);
        }


        //считываем положение каретки
        fgets(tape, sizeof(tape), input);
        if (tape == NULL) {
            printf("Error 8 : File reading error: no enough strings in file %s", fileName);
            exit(8);
        }
        int i = 0;
        while(tape[i] != '!' && tape[i] != '\n' && tape[i] != '\0'){
            i++;
        }

        //проверка на отсутствие воскл. знака
        if (tape[i] == '\n' || tape[i] == '\0') {
            printf("Error 14: No pointer (!)\n");
            exit(14);
        }

        curListOfTapesCell->curPosition = i + 1;

        fgets(tape, sizeof(tape), input);
        if (tape == NULL) {
            printf("Error 8 : File reading error: no enough strings in file %s", fileName);
            exit(8);
        }

        //записываем ленту

        tapePart = tape;
        if(tapePart[strlen(tapePart)-1] == '\n') tapePart = strcut(tapePart,0,strlen(tapePart)-1);
        //проверка на вхождение воскл знака в ленту
        if(i >= strlen(tapePart)) {
            printf("Error 15 : Pointer out of tapes(!)");
            exit(15);
        }
        for (int i = 0; i < strlen(tapePart); ++i) {

            if (i + 1 == curListOfTapesCell->curPosition){
                curListOfTapesCell->curSymbol = tapePart[i];
            }
            struct tapeCell *curTapeCell = curListOfTapesCell->thisTape;
            while (curTapeCell->next != NULL) curTapeCell = curTapeCell->next;
            curTapeCell->data = tapePart[i];



            //добавляем крайний пустой символ
            struct tapeCell *newTapeCell = (struct tapeCell*)malloc(sizeof(*newTapeCell));
            if (newTapeCell == NULL) {
                printf("Error 16: Not enough memory.\n");
                exit(16);
            }
            newTapeCell->next = NULL;
            newTapeCell->data = voidSymbol;
            newTapeCell->prev = curTapeCell;
            newTapeCell->position = (curTapeCell->position +1);
            curTapeCell->next = newTapeCell;
        }
    }
    fclose(input);
    return tapes;
}