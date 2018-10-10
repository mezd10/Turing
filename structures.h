
#ifndef TURINGMACHINE_STRUCTURES_H
#define TURINGMACHINE_STRUCTURES_H

/* tapeNumb - номер ленты
 * curSymbol - символ под кареткой
 * curPosition - позиция каретки
 * thisTape - указатель на первый элемент ленты (левый)
 * nextTape - указатель на следующую ленту
 */
//list_of_tapes
struct listOfTapes
{
    int                 tapeNumb;
    char                curSymbol;
    int                 curPosition;
    struct tapeCell*    thisTape;
    struct listOfTapes* nextTape;
};



/* ячейка ленты
 * position - позиция данной ячейки на ленте
 * data - символ ячейки
 * next - указатель на следующую ячейку ленты
 * prev - указатель на предыдущую ячейку ленты
 */
//tape
struct tapeCell
{
    int              position;
    char             data;
    struct tapeCell* next;
    struct tapeCell* prev;
};


/* stateNumb - номер состояния
 * thisState - казатель на ячейку с состоянием перехода
 * nextState - указатель на следующее состояние
 */
//list_of_states
struct listOfStates
{
    int                  stateNumb;
    struct state*        thisState;
    struct listOfStates* nextState;
};

/* ячейка состояния
 * curCondition - текущие символы под каретками
 * newCondition - символы, которые необходимо напечатать под каретками
 * nextState - следующее состояние, в которое необходимо перейти
 * next - указатель на следующую ячейку
 */
//state
struct state {
    char*         curCondition;
    char*         newCondition;
    int           nextState;
    struct state* next;
};

void printFinalIssues();
void printIssues();
void printCurState(struct listOfTapes *tapes, int numOfStep, int curState);
void printTapes(struct listOfTapes *tapes, char *transition);
void aboutTuring();
void aboutDescription();
void aboutTape();
//inputFile
struct listOfStates* readDescription(char *file, struct listOfStates *states, int *curState, int *numOfTapes);
char *strcut(char *string, int fromIndex, int toIndex);
void splitState(char state[], struct listOfStates *states);

//inputTapes
struct listOfTapes* readTapes(char *fileName, struct listOfTapes *tapes, char voidSymbol, int numOfTapes);

//outputFile
void foutCondition(char *file, struct listOfTapes *tapes, int numOfStep, char *transition);

//TuringAlgorithm
void step(struct listOfTapes *tapes, struct listOfStates *states, char voidSymbol, int numOfStep, int *curState, struct state *curStateCell, char** transition);

#endif //TURINGMACHINE_STRUCTURES_H
