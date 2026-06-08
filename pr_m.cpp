#include <iostream>
#include "pr.h"
#include <string>

void promt() {
    std::cout << std::endl << "Подсказка: " << std::endl
              << "~ Вид постфиксной записи: a b операция" << std::endl
              << "~ Операнды: положительные вещественные числа" << std::endl
              << "~ Доступные операции: + - * /" << std::endl 
              << "~ Между числами и знаками строго 1 пробел" << std::endl << std::endl; 
}

void one() {
    promt();

    std::string str;
    std::cout << "Введите ваше выражение: ";
    std::getline(std::cin, str);

    if (!check::is_valid_str(str)) {
        std::cout << "!Ошибка. Некорректная строка на входе." << std::endl;
        return;
    }

    postfix_exp pexp(str);

    pexp.method_postfix();
}