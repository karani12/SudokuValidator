#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

pthread_t threads[11];
int grid[9][9] = {
        {5, 3, 4, 6, 7, 8, 9, 1, 2},
        {6, 7, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9}
};

typedef struct {
    int row;
    int column;
    int subgridIndex;
} Parameters;


int results[11];

void validateColumn(void *arg) {
    Parameters *data = (Parameters *) arg;
    int column = data->column;
    int seen[10] = {0};

    for (int row = 0; row < 9; row++) {
        int value = grid[row][column];
        if (seen[value] || value == 0) {
            results[0] = 0;
            return;
        }
        seen[value] = 1;


    }
    results[0] = 1;

}


void validateRow(void *arg) {
    Parameters *data = (Parameters *) arg;
    int row = data->row;
    int seen[10] = {0};

    for (int column = 0; column < 9; ++column) {
        int value = grid[column][row];

        if (seen[value] || value == 0) {
            results[1] = 0;
            return;
        }
        seen[value] = 1;

    }
    results[1] = 1;
}

void validateSubgrid(void *arg) {
    Parameters *data = (Parameters *) arg;
    int subgridIndex = data->subgridIndex;
    int row = subgridIndex / 3 * 3;
    int column = subgridIndex % 3 * 3;

    int seen[10] = {0};


    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            int value = grid[row + i][column + j];
            if (seen[value] || value == 0) {
                results[subgridIndex + 1] = 0;
                return;
            }
            seen[value] = 1;
        }
    }

    results[subgridIndex + 1] = 1;
}

void main() {
    for (int i = 0; i < 9; i++) {
        Parameters *data = malloc(sizeof(Parameters));
        data->subgridIndex = i;
        pthread_create(&threads[i], NULL, (void *(*)(void *)) validateSubgrid, data);
    }

    Parameters *data = malloc(sizeof(Parameters));
    data->column = 0;
    data->row = 0;

    pthread_create(&threads[10], NULL, (void *(*)(void *)) validateColumn, data);
    pthread_create(&threads[11], NULL, (void *(*)(void *)) validateRow, data);

    int valid = 1;
    for (int i = 1; i <= 9; i++) {
        if (results[i] == 0) {
            valid = 0;
            break;
        }
    }

    if (valid) {
        printf("Sudoku puzzle is valid.\n");
    } else {
        printf("Sudoku puzzle is invalid.\n");
    }


}



