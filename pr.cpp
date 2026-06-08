#include <iostream>
#include "pr.h"
#include <windows.h>

int menu() {
    std::cout << std::endl << "!! Меню:" << std::endl
              << "1. Вычислить заданное выражение;" << std::endl
              << "0. Выход." << std::endl
              << "Ваш выбор? ";
    return check::valid_action();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << std::endl << "----Калькулятор постфиксных выражений----";
    int choice;
    do {
        choice = menu();
        switch (choice) {
            case 1: {
                one();
                std::cout << "Возврат в меню..." << std::endl << std::endl;
                break;
            } case 0: {
                std::cout << "Завершение работы..." << std::endl
                          << "Работа завершена." << std::endl;
                break;
            } default: {
                std::cout << "!Ошибка. Ожидается ввод в диапазоне от 0 до 1." << std::endl;
                break;
            }
        }
    } while (choice != 0);
    return 0;
}