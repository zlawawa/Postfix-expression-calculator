#include <iostream>
#include "pr.h"
#include <windows.h>

int Menu() {
    std::cout << std::endl << "!! Меню:" << std::endl
              << "1. Вычислить заданное выражение;" << std::endl
              << "0. Выход." << std::endl
              << "Ваш выбор? ";
    return Check::ValidAction();
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << std::endl << "----Калькулятор постфиксных выражений----";
    int choice;
    do {
        choice = Menu();
        switch (choice) {
            case 1: {
                One();
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