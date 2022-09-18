#include <iostream>
#include "functions.h"


int input(){
    int a = 0;
    while(!(std::cin >> a).good()){
        std::cout << "Неправильно введено число. Попробуйте ещё раз.\n";
        //std::cin.clear();
        //std::cin.ignore(1000, '\n');
    }
    std::cin.clear();
    std::cin.ignore(1000, '\n');
    return a;
}

int make_matrix(Matrix* matrix, int nx, int my, int amount){
    matrix->amount = amount;
    matrix->nx = nx;
    matrix->my = my;
    int flag = 0;
    for(int i = 0; i < amount; i++){
        flag = insert(matrix, nx, my);
        while(flag){
            flag = insert(matrix, nx, my);
        }
    }
    return 0;
}

int insert(Matrix* matrix, int nx, int my){
    std::cout << "Введите номер строки:\n";
    int y = input();
    while(y > my){
        std::cout << "Вы вышли за рамки таблицы. Попробуйте ещё раз.\n";
        y = input();
    }
    std::cout << "Введите номер столбца:\n";
    int x = input();
    while(x > nx){
        std::cout << "Вы вышли за рамки таблицы. Попробуйте ещё раз.\n";
        x = input();
    }
    std::cout << "Введите значение ячейки:\n";
    int inf = input();
    if(matrix->rows == nullptr){
        matrix->rows = new Row;
        matrix->rows->y = y;
        matrix->rows->cells = new Cell;
        matrix->rows->cells->inf = inf;
        matrix->rows->cells->x = x;
        matrix->rows->cells->next_c = nullptr;
        matrix->rows->next_r = nullptr;
        return 0;
    }
    Row* tmp_row = matrix->rows;
    if(y < tmp_row->y){
        Row* new_row = new Row;
        new_row->y = y;
        new_row->cells = new Cell ;
        new_row->cells->x = x;
        new_row->cells->inf = inf;
        new_row->cells->next_c = nullptr;
        new_row->next_r = nullptr;
        new_row->next_r = matrix->rows;
        matrix->rows = new_row;
        return 0;
    }else if(y == tmp_row->y){
        Cell* tmp_cell = tmp_row->cells;
        if(x < tmp_cell->x){
            Cell* new_cell = new Cell;
            new_cell->x = x;
            new_cell->inf = inf;
            new_cell->next_c = tmp_row->cells;
            tmp_row->cells = new_cell;
            return 0;
        }else if(x == tmp_cell->x){
            std::cout << "В этой ячейке элемент уже присутствует. Попробуйте ещё раз.\n";
            return 1;
        }else{
            while((tmp_cell->next_c != nullptr) && (tmp_cell->next_c->x < x)){
                tmp_cell = tmp_cell->next_c;
            }
            Cell* new_cell = new Cell;
            new_cell->x = x;
            new_cell->inf = inf;
            new_cell->next_c = tmp_cell->next_c;
            tmp_cell->next_c = new_cell;
            return 0;
        }
    }else{
        while((tmp_row->next_r != nullptr) && (tmp_row->next_r->y < y)){
            tmp_row = tmp_row->next_r;
        }
        Row* new_row = new Row;
        new_row->y = y;
        new_row->next_r = tmp_row->next_r;
        new_row->cells = new Cell;
        new_row->cells->x = x;
        new_row->cells->inf = inf;
        new_row->cells->next_c = nullptr;
        tmp_row->next_r = new_row;
        return 0;
    }
}

Row* search_max(Matrix* matrix, int maxi){
    Row* tmp_row = matrix->rows;
    Row* max_row = nullptr;
    while(tmp_row != nullptr){
        if((tmp_row->cells->inf >= maxi) && (tmp_row->f != 1)){
            maxi = tmp_row->cells->inf;
            max_row = tmp_row;
        }
        tmp_row = tmp_row->next_r;
    }
    return max_row;
}

Row* search_min(Matrix* matrix, int mini){
    Row* tmp_row = matrix->rows;
    Row* min_row = nullptr;
    while(tmp_row != nullptr){
        if(tmp_row->f != 1){
            if(tmp_row->cells->inf <= mini){
                mini = tmp_row->cells->inf;
                min_row = tmp_row;
            }
        }
        tmp_row = tmp_row->next_r;
    }
    return min_row;
}

int changing(Matrix* matrix, Matrix* new_matrix){
    new_matrix->amount = matrix->amount;
    new_matrix->my = matrix->my;
    new_matrix->nx = matrix->nx;
    new_matrix->rows = new Row;
    Row* tmp_row_max = search_max(matrix, 0);
    Row* tmp_row_min = search_min(matrix, 10000);
    tmp_row_min->f = 1;
    new_matrix->rows->y = matrix->rows->y;
    new_matrix->rows->cells = new Cell;
    new_matrix->rows->cells->inf = tmp_row_min->cells->inf;
    new_matrix->rows->cells->x = tmp_row_min->cells->x;
    Cell* tmp_cell = tmp_row_min->cells->next_c;
    Cell* tmp_new_cell = new_matrix->rows->cells;
    while(tmp_cell != nullptr){
        tmp_new_cell->next_c = new Cell;
        tmp_new_cell->next_c->inf = tmp_cell->inf;
        tmp_new_cell->next_c->x = tmp_cell->x;
        tmp_cell = tmp_cell->next_c;
        tmp_new_cell = tmp_new_cell->next_c;
    }
    Row* tmp_row_old = matrix->rows;
    Row* tmp_row = new_matrix->rows;

    while(tmp_row_min != tmp_row_max){
        tmp_row_min = search_min(matrix, 10000);
        tmp_row_min->f = 1;
        tmp_cell = tmp_row_min->cells->next_c;
        tmp_row->next_r = new Row;
        tmp_row->next_r->y = tmp_row_old->next_r->y;
        tmp_row->next_r->cells = new Cell;
        tmp_row->next_r->cells->inf = tmp_row_min->cells->inf;
        tmp_row->next_r->cells->x = tmp_row_min->cells->x;
        while(tmp_cell != nullptr){
            tmp_new_cell->next_c = new Cell;
            tmp_new_cell->next_c->inf = tmp_cell->inf;
            tmp_new_cell->next_c->x = tmp_cell->x;
            tmp_cell = tmp_cell->next_c;
            tmp_new_cell = tmp_new_cell->next_c;
        }
        tmp_row = tmp_row->next_r;
        tmp_row_old = tmp_row_old->next_r;
    }
    return 0;
}

int output(Matrix* matrix){
    if(matrix->rows == nullptr){
        std::cout << "Матрица не создана. \n";
        return 1;
    }
    Row* tmp_row = matrix->rows;
    Cell* tmp_cell = tmp_row->cells;
    while(tmp_row != nullptr) {
        while (tmp_cell != nullptr) {
            std::cout << tmp_cell->inf << "(" << tmp_row->y << ", " << tmp_cell->x << ")\n";
            tmp_cell = tmp_cell->next_c;
        }
        tmp_row = tmp_row->next_r;
        if(tmp_row != nullptr) {
            tmp_cell = tmp_row->cells;
        }
    }
    return 0;
}


int free_all(Matrix* maxtrix){
    if(maxtrix->rows == nullptr){
        std::cout << "Матрица не создана. \n";
        return 1;
    }
    Row* tmp_row = maxtrix->rows;
    Cell* tmp_cell = tmp_row->cells;
    Cell* deleted_cell = nullptr;
    Row* deleted_row = nullptr;
    while(tmp_row != nullptr) {
        while (tmp_cell != nullptr) {
            deleted_cell = tmp_cell;
            tmp_cell = tmp_cell->next_c;
            delete deleted_cell;
        }
        deleted_row = tmp_row;
        tmp_row = tmp_row->next_r;
        if(tmp_row != nullptr) {
            tmp_cell = tmp_row->cells;
        }
        delete deleted_row;
    }
    return 0;
}