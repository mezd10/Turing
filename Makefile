progT.exe : main.o inputFile.o inputTapes.o TuringAlgorithm.o outputFile.o printHelps.o 
	gcc -o progr main.o inputFile.o inputTapes.o TuringAlgorithm.o outputFile.o printHelps.o
main.o: main.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o main.o main.c
inputFile.o : inputFile.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o inputFile.o inputFile.c 
inputTapes.o : inputTapes.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o inputTapes.o inputTapes.c
TuringAlgorithm.o : TuringAlgorithm.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o TuringAlgorithm.o TuringAlgorithm.c
outputFile.o : outputFile.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o outputFile.o outputFile.c
printHelps.o : printHelps.c
	gcc -std=c11 -pedantic -Wall -Wextra -c -o printHelps.o printHelps.c