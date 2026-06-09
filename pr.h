#include <iostream>
#include <limits>
#include <string>

class Check {
public:
    static int ValidAction() {
        int value;
        while(!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "!Ошибка. Ожидается целое число... Попробуйте ещё раз: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return value;
    }

    static bool IsValidStr(std::string line) {
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

class CalcException : public std::exception {
private:
    std::string m_error;

public:
    CalcException(std::string error) : m_error{ error } {}
    const char* what() const noexcept override { return m_error.c_str(); }
};

class Stack {
private:
    struct Node {
        double value;
        Node* next;
    };
    Node* top;

public:
    Stack(const Stack&) = delete;

    Stack& operator=(const Stack&) = delete;

    Stack() { top = nullptr; }

    ~Stack() { 
        while (top != nullptr) {
            Node* temp_node = top;
            top = top->next;
            delete temp_node;
        }
    }

    void Push(double v) {
        Node* new_node = new Node;
        new_node->value = v;
        new_node->next = top;
        top = new_node;
    } 

    void Pop() {
        if (is_empty()) { return; }
        Node* temp_node = top;
        top = temp_node->next;
        delete temp_node;
    }

    double get_top() const { 
        if (is_empty()) { throw CalcException("!Ошибка. Стек пуст."); }
        return top->value; 
    }

    bool is_empty() const {
        if (top == nullptr) { return true; }
        return false;
    }

    int GetQuantity() const {
        Node* temp_node = top;
        int cnt = 0;
        while (temp_node != nullptr) {
            cnt++;
            temp_node = temp_node->next;
        }
        return cnt;
    }

};

class PostfixExp {
private:
    std::string text;

    double IsOperation(double a, double b, std::string op) {
        if (op == "+") { return a + b; }
        else if (op == "-") { return a - b; }
        else if (op == "*") { return a * b; }
        else if (op == "/") { 
            if (b != 0) {
                return a / b; 
            } else {
                throw CalcException("!Ошибка. Деление на 0 невозможно...");
            }
        }
        else { return 0.0; }
    }

public:
    PostfixExp(std::string line) { text = line; }

    void MethodPostfix() {
        Stack expression;
        std::string token;
        
        for (int i = 0; i <= text.size(); i++) {
            if (i < text.size() && text[i] != ' ') {
                token += text[i];
            } else {
                if (token.empty()) { continue; }
                
                try {
                    double value = std::stod(token);
                    if (value < 0) { std::cout << "!Ошибка. Ожидались положительные числа..." << std::endl; return; }
                    expression.Push(value);
                } catch (...) {
                    /* так как std::stod не смог преобразовать токен в вещ. число, значит это знак операции,
                       достаём правый и левый операнд из стека для выполнения операции */
                    if (expression.is_empty()) { std::cout << "!Ошибка. Некорректное выражение." << std::endl; return; }
                    double b = expression.get_top();
                    expression.Pop();

                    if (expression.is_empty()) { std::cout << "!Ошибка. Некорректное выражение." << std::endl; return; }
                    double a = expression.get_top();
                    expression.Pop();

                    try {
                        double temp = IsOperation(a, b, token);
                        expression.Push(temp);
                    } catch (const CalcException& c) {
                        std::cout << c.what() << std::endl;
                        return;
                    }
                }
                token = "";
            }
        }
        if (expression.GetQuantity() != 1) { std::cout << "!Ошибка. Некорректное выражение." << std::endl; return; }
        std::cout << "Результат: " << expression.get_top() << std::endl;
    }
};

void One();