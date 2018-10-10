#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "structures.h"

/*
 * открываем нужный файл для чтения
 * считываем строчку, содержащую кол-во лент
 * * обрабатываем её на равенство NULL
 * считываем строчку с алфавитом
 * * обрабатываем её на равенство NULL
 * считываем строчку и выделяем из неё номер начального состояния машины
 * * обрабатываем её на равенство NULL
 * построчно считываем состояния переходов и передаём их в splitState для обработки
 *
 * аргументы:
 * * file - имя входного файла
 * * states - структура состояний
 * * curState - текущее состояние
 * *numOfTapes - количество лент
 */
struct listOfStates* readDescription(char *file, struct listOfStates *states, int *curState, int *numOfTapes) {

    char *alfabet;

    //открываем файл
    FILE *input;
    input = fopen(file, "r");
    if (input == NULL) {
        printf("Error 2 : File \"%s\" can't be open", file);
        exit(2);
    }

    char tmpLine[2000000];
    //читаем кол-во лент
    fgets(tmpLine, sizeof(tmpLine), input);
    *numOfTapes = atoi(tmpLine);
    if (*numOfTapes == 0) {
        printf("Error 3 : Wrong number of tapes.");
        exit(3);
    }


    //читаем алфавит
    fgets(tmpLine, sizeof(tmpLine), input);
    alfabet = strdup(tmpLine);


    //считываем начальное состояние
    fgets(tmpLine, sizeof(tmpLine), input);
    *curState = strtol(strcut(tmpLine, 1, strlen(tmpLine)), NULL, 0);
    if (*curState == 0) {
        printf("Error 4 : Wrong start state.");
        exit(4);
    }


    states = (struct listOfStates *) malloc(sizeof(*states));
    if (states == NULL) {
        printf("Error 16: Not enough memory.\n");
        exit(16);
    }
    states->stateNumb = 1;
    states->nextState = NULL;
    states->thisState = NULL;
    //считываем состояния
    while (fgets(tmpLine, sizeof(tmpLine), input)) {
        splitState(tmpLine, states);
    }

    fclose(input);
    return states;
}

char *strcut(char *string, int fromIndex, int toIndex) {
    if (strlen(string) == 0)
        return string;
    char *result = strdup(string);
    if (toIndex > strlen(string) + 1)
        toIndex = strlen(string) + 1;
    int length = toIndex - fromIndex;
    if (length < 0) return "";
    if (length == 0) result[0] = string[fromIndex];
    for (int i = fromIndex; i < toIndex; ++i) {
        result[i - fromIndex] = string[i];
    }
    result[length] = '\0';
    return result;
}

/*
 * получаем на вход строку с состояниями переходов
 * избавляемся от символа переноса строки
 * разбиваем строчку по первому пробелу, определяем номер состояния
 * разбивая строку по остальным пробелам, выделяем каждый переход и обрабатываем его
 * * разбиваем его по символам "->"
 * * вносим в структуру stateCell состояние символов под каретками до перехода
 * * вносим в структуру stateCell состояние символов под каретками после перехода
 * * вносим в структуру stateCell следующее состояние, в которое необходимо перейти
 * * вносим полученную структуру listOfStatesCell в общую структуру состояний
 *
 * аргументы:
 * * state[] - состояние переходов
 * * states - структура состояний
 */
void splitState(char state[], struct listOfStates *states) {

    struct listOfStates *newListOfStatesCell = (states->thisState == NULL) ? states :
                                               (struct listOfStates *) malloc(sizeof(*newListOfStatesCell));
    if (newListOfStatesCell == NULL) {
        printf("Error 16: Not enough memory.\n");
        exit(16);
    }
    newListOfStatesCell->nextState = NULL;

    //определяем номер состояния
    if (state[strlen(state)] == '\n') state = strcut(state, 0, strlen(state) - 1); // избавляемся от переноса строки
    char *statePart = strdup(state);
    statePart = strtok(statePart, " ");
    state = strcut(state, strlen(statePart) + 1, strlen(state));
    newListOfStatesCell->stateNumb = strtol(strcut(statePart, 1, strlen(statePart) - 1), NULL, 0);

    struct state *prevStateCell = NULL;
    strcpy(statePart, state);
    statePart = strtok(statePart, " ");
    state = strcut(state, strlen(statePart) + 1, strlen(state));
    while (statePart != NULL) {
        struct state *newStateCell = (struct state *) malloc(sizeof(*newStateCell));
        if (newStateCell == NULL) {
            printf("Error 16: Not enough memory.\n");
            exit(16);
        }
        if (prevStateCell == NULL) newListOfStatesCell->thisState = newStateCell;
        else prevStateCell->next = newStateCell;


        newStateCell->curCondition = strdup(strtok(statePart, "->"));
        newStateCell->newCondition = strdup(strtok(NULL, "->"));
        char *newState = strtok(NULL, "->");
        newState = strcut(newState, 1, strlen(newState) - 1);
        newStateCell->nextState = strtol(newState, NULL, 0);
        newStateCell->next = NULL;

        prevStateCell = newStateCell;
        strcpy(statePart, state);
        statePart = strtok(statePart, " ");
        if (statePart != NULL) state = strcut(state, strlen(statePart) + 1, strlen(state));
    }

    if (newListOfStatesCell != states) {
        struct listOfStates *curListOfStates = states;
        while (curListOfStates->nextState != NULL) curListOfStates = curListOfStates->nextState;
        curListOfStates->nextState = newListOfStatesCell;
    }

    free(statePart);
}
