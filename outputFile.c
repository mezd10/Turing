#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "structures.h"

/*
 * вывод данных в файл
 * аргументы:
 * * file - имя выдоного файла
 * * tapes - структура лент
 * * numOfStep - номер шага
 * * transition - состояние перехода
 */
void foutCondition(char *file, struct listOfTapes *tapes, int numOfStep, char *transition) {
    FILE *output;
    output = fopen(file, "w");


   fprintf(output, "Number of steps: %i;\n", numOfStep);
   struct listOfTapes *curListOfTapesCell = tapes;
   char *curStates = NULL;
   char *nextStates = NULL;
   char *pereTransition = strdup(transition);
    if (pereTransition != NULL) {
        curStates = strtok(pereTransition, "->");
        nextStates = strtok(NULL, "->");
    }

   while (curListOfTapesCell != NULL) {
       fprintf(output, "Tape number: %i;\nPosition: %i;\nCurrent symbol: %c;\nTape:",
               curListOfTapesCell->tapeNumb, curListOfTapesCell->curPosition, curListOfTapesCell->curSymbol);
       struct tapeCell *curTapeCell = curListOfTapesCell->thisTape;

       fprintf(output,"\n");

       if (pereTransition != NULL) {
           fprintf(output, "Commands :");
           fprintf(output,"%c -> %c, %c; \n", curStates[0], nextStates[0], nextStates[2]);
           curStates = strcut(curStates, 2, strlen(curStates) + 1);
           nextStates = strcut(nextStates, 4, strlen(nextStates) + 1);
       }
       // вывод положения каретки
       while (curTapeCell != NULL) {
           if (curListOfTapesCell->curPosition == curTapeCell->position) fprintf(output,"!");
           else fprintf(output,".");
           curTapeCell = curTapeCell->next;
       }
       fprintf(output,"\n");

       curTapeCell = curListOfTapesCell->thisTape;
       // вывод ленты
       while (curTapeCell != NULL) {
           fprintf(output, "%c", curTapeCell->data);
           curTapeCell = curTapeCell->next;
       }
       fputs("\n\n", output);
       curListOfTapesCell = curListOfTapesCell->nextTape;
   }

    fclose(output);
}

