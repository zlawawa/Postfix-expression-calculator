#include <iostream>
#include "pr.h"
#include <string>

void Promt() {
    std::cout << std::endl << "Подсказка: " << std::endl
              << "~ Вид постфиксной записи: a b операция" << std::endl
              << "~ Операнды: положительные вещественные числа" << std::endl
              << "~ Доступные операции: + - * /" << std::endl 
              << "~ Между числами и знаками строго 1 пробел" << std::endl << std::endl; 
}

void One() {
    Promt();

    std::string str;
    std::cout << "Введите ваше выражение: ";
    std::getline(std::cin, str);

    if (!Check::IsValidStr(str)) {
        std::cout << "!Ошибка. Некорректная строка на входе." << std::endl;
        return;
    }

    PostfixExp pexp(str);

    pexp.MethodPostfix();
}