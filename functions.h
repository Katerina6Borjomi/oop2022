#ifndef UNTITLED_FUNCTIONS_H
#define UNTITLED_FUNCTIONS_H

typedef struct Cell{
    int x;
    int inf;
    struct Cell* next_c = nullptr;
}Cell;

typedef struct Row{
    int y;
    int f = 0;
    Cell* cells = nullptr;
    struct Row* next_r = nullptr;
}Row;

typedef struct Matrix{
    int nx;
    int my;
    int amount;
    Row* rows = nullptr;
}Matrix;

int input();
int make_matrix(Matrix* matrix, int nx, int my, int amount);
int insert(Matrix* matrix, int nx, int my);
Row* search_max(Matrix* matrix, int maxi);
Row* search_min(Matrix* matrix, int mini);
int changing(Matrix* matrix, Matrix* new_matrix);
int output(Matrix* matrix);
int free_all(Matrix* maxtrix);

#endif //UNTITLED_FUNCTIONS_H
