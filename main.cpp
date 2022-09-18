#include <iostream>
#include "functions.h"

int main() {
    //std::cout << "Hello, World!" << std::endl;
    //ввод
    Matrix matrix;
    Matrix new_matrix;

    std::cout << "Введите количество столбцов: " << std::endl;
    int nx = input();
    while(nx == 0){
        std::cout << "Количество не может быть нулевым. Попробуйте ещё раз.\n";
        std::cout << "Введите количество столбцов: " << std::endl;
        nx = input();
    }
    std::cout << "Введите количество строк: " << std::endl;
    int my = input();
    while(my == 0){
        std::cout << "Количество не может быть нулевым. Попробуйте ещё раз.\n";
        std::cout << "Введите количество строк: " << std::endl;
        my = input();
    }
    std::cout << "Введите количество элементов: " << std::endl;
    int amount = input();
    while(amount == 0) {
        std::cout << "Количество не может быть нулевым. Попробуйте ещё раз.\n";
        std::cout << "Введите количество элементов: " << std::endl;
        amount = input();
    }
    make_matrix(&matrix, nx, my, amount);

    changing(&matrix, &new_matrix);

    output(&matrix);
    std::cout << "-------------------------------\n";
    output(&new_matrix);

    free_all(&matrix);
    //delete &matrix;
    free_all(&new_matrix);
    //delete &matrix;
    return 0;
}
