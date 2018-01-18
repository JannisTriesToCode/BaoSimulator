#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

unsigned int nextStep(unsigned int currentField, unsigned int* board, unsigned int columns, unsigned int numberStonesInHand, int direction) {
	int arrayDirection = direction;
	if ((currentField / columns) % 2 == 1) {
		arrayDirection *= -1;
	}

	unsigned int border = arrayDirection == 1 ? columns - 1 : 0;

	if (currentField % columns == border) { //left or right border
		if ((currentField / columns) % 2 == 1) {
			currentField -= columns;
		} else {
			currentField += columns;
		}
	} else { //mid
		currentField += arrayDirection;
	}

	numberStonesInHand--;
	board[currentField]++;

	if (numberStonesInHand != 0) {
		return nextStep(currentField, board, columns, numberStonesInHand, direction);
	}

	return currentField;
}

void printBoard(unsigned int currentField, unsigned int* board, unsigned int columns, unsigned int numberStonesInHand) {
	for (unsigned int row = 0; row < 4; row++) {
		for (unsigned int column = 0; column < columns; column++) {
			if (currentField == row * columns + column) {
				printf("[%d]\t", board[row * columns + column]);
			} else {
				printf("%d\t", board[row * columns + column]);
			}
		}
		printf("\n");
	}
}

int main() {
	unsigned int columns;
	//unsigned int *board;
	unsigned int currentField;
	unsigned int numberStonesInHand = 0;
	unsigned int currentRow;
	unsigned int currentColumn;
	int direction, counter = 0;
	printf("##### Bao Sim #####\n\nType in the number of columns:\t");
	scanf_s("%u", &columns);
	fflush(stdin);

	unsigned int board[] = { 0, 2, 4, 3, 2, 1, 2, 0, 4, 0, 1, 2, 8, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,0, 2, 2, 1, 0, 1, 4, 6, 0 };
	unsigned int boardCopy[] = { 0, 2, 4, 3, 2, 1, 2, 0, 4, 0, 1, 2, 8, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0 ,0, 2, 2, 1, 0, 1, 4, 6, 0 };
	
	unsigned int currentFieldCopy;
	/*board = (unsigned int*)calloc(columns * 4, sizeof(unsigned int));
	
	for (unsigned int row = 0; row < 4; row++) {
		for (unsigned int column = 0; column < columns; column++) {
			printf("Number of stones in [%d:%d]:\t", row + 1, column + 1);
			scanf_s("%u", &board[row*columns + column]);
			fflush(stdin);
		}
	}*/

	do {
		printf("\nType in your current row and column:\t");
		scanf_s("%u%u", &currentRow, &currentColumn);
		fflush(stdin);
		currentField = (currentRow - 1) * columns + currentColumn - 1;
		if (board[currentField] < 2) {
			printf("No moves possible!\n");
		}
	} while (board[currentField] < 2);

	currentFieldCopy = currentField;

	do {
		printf("\nType in your direction (-1: counterclockwise | 1: clockwise):\t");
		scanf_s("%d", &direction);
		fflush(stdin);
		if (direction != 1 && direction != -1) {
			printf("Invalid Direction!\n");
		}
	} while (direction != 1 && direction != -1);

	int sameBoard;

	printBoard(currentField, board, columns, numberStonesInHand);
	while (board[currentField] > 1) {
		//system("pause");
		counter++;
		numberStonesInHand = board[currentField];
		board[currentField] = 0;
		currentField = nextStep(currentField, board, columns, numberStonesInHand, direction);
		printf("\n");
		printBoard(currentField, board, columns, numberStonesInHand);
		printf("Counter: %d\n\n", counter);	
		if (currentField == currentFieldCopy) {
			sameBoard = 1;
			for (unsigned int i = 0; i < columns * 4; i++) {
				if (board[i] != boardCopy[i]) {
					sameBoard = 0;
					break;
				}
			}
			if (sameBoard == 1) {
				printf("\nWelcome to the infinite game mode. Your partner may leave the room now. Enjoy the game!\nYou will reach the same state every %d steps\n\n", counter);
				system("pause");
			}
		}
	}
	printf("\n\n");
	printBoard(currentField, board, columns, numberStonesInHand);
	printf("\n\nCounter: %d\n\n", counter);	
	system("pause");
}