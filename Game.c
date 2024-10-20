#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4
#define MAX_TRIES 10

void initializeBoard(char board[SIZE][SIZE], int revealed[SIZE][SIZE]) {
    char cards[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
    
    srand(time(0));
    for (int i = 0; i < SIZE * SIZE; i++) {
        int j = rand() % (SIZE * SIZE);
        char temp = cards[i];
        cards[i] = cards[j];
        cards[j] = temp;
    }
    
    int index = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = cards[index++];
            revealed[i][j] = 0;
        }
    }
}

void displayBoard(char board[SIZE][SIZE], int revealed[SIZE][SIZE]) {
    printf("    ");
    for (int col = 0; col < SIZE; col++) {
        printf(" %d  ", col);
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf("%d | ", i);
        for (int j = 0; j < SIZE; j++) {
            if (revealed[i][j]) {
                printf(" %c ", board[i][j]);
            } else {
                printf(" * ");
            }
        }
        printf("\n");
    }
}

int checkMatch(char board[SIZE][SIZE], int revealed[SIZE][SIZE], int x1, int y1, int x2, int y2) {
    if (board[x1][y1] == board[x2][y2]) {
        revealed[x1][y1] = 1;
        revealed[x2][y2] = 1;
        return 1;
    } else {
        return 0;
    }
}

int gameWon(int revealed[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!revealed[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int main() {
    char board[SIZE][SIZE];
    int revealed[SIZE][SIZE];
    int x1, y1, x2, y2;
    int tries = 0;
    
    initializeBoard(board, revealed);
    
    while (!gameWon(revealed) && tries < MAX_TRIES) {
        displayBoard(board, revealed);
        
        printf("Attempt %d of %d\n", tries + 1, MAX_TRIES);
        printf("Select first card (row & column): \n");
        scanf("%d %d", &x1, &y1);
        printf("Select second card (row & column): \n");
        scanf("%d %d", &x2, &y2);
        
        if (checkMatch(board, revealed, x1, y1, x2, y2)) {
            printf("\nMatch found!\n\n");
        } else {
            printf("\nNo match. Try again.\n\n");
        }
        
        tries++;
    }
    
    if (gameWon(revealed)) {
        printf("\nCongratulations! You've won the game!\n");
    } else {
        printf("\nYou've reached the maximum number of tries. Game over!\n");
    }
    
    return 0;
}
