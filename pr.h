#include <iostream>
#include <limits>
#include <string>

class check {
public:
    static int valid_action() {
        int value;
        while(!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "!Ошибка. Ожидается целое число... Попробуйте ещё раз: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }

    static bool is_valid_str(std::string line) {
        if (line.empty()) {
            std::cout << "!Ошибка. Выражение пустое." << std::endl;
            return false;
        }
        if (line[0] == ' ' || line[line.size() - 1] == ' ') { return false; }

        for (int i = 0; i < line.size(); i++) {
            if (i < line.size() - 1 && line[i] == ' ' 
                                    && line[i + 1] == ' ') { return false; }
            if (!(std::isdigit(line[i])) && (line[i] != '*')
                                         && (line[i] != '/') 
                                         && (line[i] != '-') 
                                         && (line[i] != '+') 
                                         && (line[i] != ' ') 
                                         && (line[i] != '.')) { return false; }
        }
        return true;
    }
};

class calc_exception : public std::exception {
private:
    std::string m_error;
public:
    calc_exception(std::string error) : m_error{ error } {}
    const char* what() const noexcept override { return m_error.c_str(); }
};

class stack {
private:
    struct Node {
        double value;
        Node* next;
    };
    Node* top;

public:
    stack(const stack&) = delete;

    stack& operator=(const stack&) = delete;

    stack() { top = nullptr; }

    ~stack() { 
        while (top != nullptr) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    void push(double v) {
        Node* newNode = new Node;
        newNode->value = v;
        newNode->next = top;
        top = newNode;
    } 

    void pop() {
        if (is_empty()) { return; }
        Node* tempNode = top;
        top = tempNode->next;
        delete tempNode;
    }

    double get_top() { 
        if (is_empty()) { throw calc_exception("!Ошибка. Стек пуст."); }
        return top->value; 
    }

    bool is_empty() {
        if (top == nullptr) { return true; }
        return false;
    }

    int get_quantity() {
        Node* temp = top;
        int cnt = 0;
        while (temp != nullptr) {
            cnt++;
            temp = temp->next;
        }
        return cnt;
    }

};

class postfix_exp {
private:
    std::string text;

    double is_operation(double a, double b, std::string op) {
        if (op == "+") { return a + b; }
        else if (op == "-") { return a - b; }
        else if (op == "*") { return a * b; }
        else if (op == "/") { 
            if (b != 0) {
                return a / b; 
            } else {
                throw calc_exception("!Ошибка. Деление на 0 невозможно...");
            }
        }
        else { return 0.0; }
    }
public:
    postfix_exp(std::string line) { text = line; }

    void method_postfix() {
        stack expression;
        std::string token;
        
        for (int i = 0; i <= text.size(); i++) {
            if (i < text.size() && text[i] != ' ') {
                token += text[i];
            } else {
                if (token.empty()) { continue; }

                try {
                    double value = std::stod(token);
                    if (value < 0) { std::cout << "!Ошибка. Ожидались положительные числа..." << std::endl; return; }
                    expression.push(value);
                } catch (...) {
                    /* так как std::stod не смог преобразовать токен в вещ. число, значит это знак операции,
                       достаём правый и левый операнд из стека для выполнения операции */
                    if (expression.is_empty()) { std::cout << "!Ошибка. Некорректное выражение." << std::endl; return; }
                    double b = expression.get_top();
                    expression.pop();

                    if (expression.is_empty()) { std::cout << "!Ошибка. Некорректное выражение." << std::endl; return; }
                    double a = expression.get_top();
                    expression.pop();

                    try {
                        double temp = is_operation(a, b, token);
                        expression.push(temp);
                    } catch (const calc_exception& c) {
                        std::cout << c.what() << std::endl;
                        return;
                    }
                }
                token = "";
            }
        }
        if (expression.get_quantity() != 1) { std::cout << "!Ошибка. Некорректное выражение." << std::endl; return; }
        std::cout << "Результат: " << expression.get_top() << std::endl;
    }
};

void one();