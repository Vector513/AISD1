#include "sortingStation.h"
#include "stack.h"
#include <sstream>
#include <cctype>
#include <cmath>
#include <iostream>

SortingStation::SortingStation() : tokensInf(), tokensPost() {}

SortingStation::~SortingStation() {}

// Функция очистки токенов перед новым выражением
void SortingStation::clear() {
    tokensInf.clear();
    tokensPost.clear();
}

// Токенизация строки в инфиксную или постфиксную запись
bool SortingStation::tokenize(const std::string& input, bool isInf)
{

    std::string token;
    std::istringstream stream(input);
    int openBrackets = 0;
    int closeBrackets = 0;
    int operands = 0;
    int operators = 0;

    for (size_t i = 0; i < input.length(); ++i) {
        char c = input[i];

        if (std::isdigit(c)) {
            token += c;
        }
        else {
            if (!token.empty()) {
                if (isInf) {
                    tokensInf.emplace_back("value", token);
                }
                else {
                    tokensPost.emplace_back("value", token);
                }
                token.clear();
                ++operands;
            }

            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
                if (isInf) {
                    tokensInf.emplace_back("operator", std::string(1, c));
                }
                else {
                    tokensPost.emplace_back("operator", std::string(1, c));
                }
                ++operators;
            }
            else if (c == '(') {
                if (isInf) {
                    tokensInf.emplace_back("operator", std::string(1, c));
                }
                else {
                    tokensPost.emplace_back("operator", std::string(1, c));
                }
                ++openBrackets;
            }
            else if (c == ')') {
                if (isInf) {
                    tokensInf.emplace_back("operator", std::string(1, c));
                }
                else {
                    tokensPost.emplace_back("operator", std::string(1, c));
                }
                ++closeBrackets;
            }
            else if (input.substr(i, 3) == "sin") {
                if (isInf) {
                    tokensInf.emplace_back("operator", "sin");
                }
                else {
                    tokensPost.emplace_back("operator", "sin");
                }
                i += 2;
            }
            else if (input.substr(i, 3) == "cos") {
                if (isInf) {
                    tokensInf.emplace_back("operator", "cos");
                }
                else {
                    tokensPost.emplace_back("operator", "cos");
                }
                i += 2;
            }
            else if (!std::isspace(c)) {
                std::cerr << "Ошибка: некорректный символ '" << c << "' в выражении.\n";
                clear();
                return false;
            }
        }
    }

    if (!token.empty()) {
        if (isInf) {
            tokensInf.emplace_back("value", token);
        }
        else {
            tokensPost.emplace_back("value", token);
        }
        ++operands;
    }

    if (operands != operators + 1) {
        std::cerr << "Ошибка: некорректное количество операторов и операндов.\n";
        clear();
        return false;
    }

    if (openBrackets != closeBrackets) {
        std::cerr << "Ошибка: некорректное количество скобок.\n";
        clear();
        return false;
    }
    return true;
}

// Функция для получения приоритета оператора
int SortingStation::getPrecedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

// Функция для проверки ассоциативности оператора
bool SortingStation::isLeftAssociative(const std::string& op) {
    return op != "^";
}

// Определяем необходимость добавления скобок
std::string SortingStation::wrapIfNeeded(const std::string& expression, const std::string& operatorSymbol, bool isLeft) {
    // Определяем, требуется ли обёртка
    if (getPrecedence(operatorSymbol) > getPrecedence(expression)) {
        return "(" + expression + ")";
    }
    return expression;
}

// Преобразование инфиксной записи в постфиксную
void SortingStation::infToPost() {
    tokensPost.clear();
    Stack<std::pair<std::string, std::string>> operatorStack;

    for (const auto& token : tokensInf) {
        const std::string& type = token.first;
        const std::string& value = token.second;

        if (type == "value") {
            tokensPost.push_back(token);
        }
        else if (type == "operator") {
            if (value == "(") {
                operatorStack.push(token);
            }
            else if (value == ")") {
                while (!operatorStack.empty() && operatorStack.top().second != "(") {
                    tokensPost.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                if (!operatorStack.empty()) {
                    operatorStack.pop();
                }
            }
            else {
                while (!operatorStack.empty() && getPrecedence(operatorStack.top().second) >= getPrecedence(value)
                    && isLeftAssociative(value)) {
                    tokensPost.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
            }
        }
    }

    while (!operatorStack.empty()) {
        tokensPost.push_back(operatorStack.top());
        operatorStack.pop();
    }
}

// Преобразование постфиксной записи в инфиксную
void SortingStation::postToInf() {
    tokensInf.clear();
    Stack<std::string> expressionStack;

    for (const auto& token : tokensPost) {
        const std::string& type = token.first;
        const std::string& value = token.second;

        if (type == "value") {
            expressionStack.push(value);
        }
        else if (type == "operator") {
            if (expressionStack.getSize() < 2) {
                throw std::runtime_error("Недостаточно операндов для оператора");
            }

            std::string rightOperand = expressionStack.top();
            expressionStack.pop();
            std::string leftOperand = expressionStack.top();
            expressionStack.pop();

            // Определяем, нужны ли скобки
            std::string newExpr = leftOperand + " " + value + " " + rightOperand;

            // Проверка, нужны ли скобки для левого операнда
            if (leftOperand.find('(') != std::string::npos) {
                // Если внутри левого операнда есть оператор, возможно, нужны скобки
                std::string leftOp = leftOperand.substr(leftOperand.find_last_of(" ") + 1);
                if (getPrecedence(leftOp) < getPrecedence(value)) {
                    newExpr = "(" + newExpr;
                }
            }

            // Проверка, нужны ли скобки для правого операнда
            if (rightOperand.find('(') != std::string::npos) {
                // Если внутри правого операнда есть оператор, возможно, нужны скобки
                std::string rightOp = rightOperand.substr(rightOperand.find_last_of(" ") + 1);
                if (getPrecedence(rightOp) <= getPrecedence(value)) {
                    newExpr += ")";
                }
            }

            expressionStack.push(newExpr);
        }
    }

    if (expressionStack.getSize() != 1) {
        throw std::runtime_error("Ошибка преобразования: стек не содержит одно итоговое выражение");
    }

    tokensInf.push_back(std::make_pair("value", expressionStack.top()));
}

// Вычисление выражения в постфиксной записи
number SortingStation::evaluatePost() {
    Stack<number> valueStack;

    for (const auto& token : tokensPost) {
        const std::string& type = token.first;
        const std::string& value = token.second;

        if (type == "value") {
            valueStack.push(std::stod(value)); // Преобразуем строку в число
        }
        else if (type == "operator") {
            if (value == "+" || value == "-" || value == "*" || value == "/" || value == "^") {
                if (valueStack.getSize() < 2) {
                    throw std::runtime_error("Недостаточно операндов для выполнения операции");
                }

                number rightOperand = valueStack.top();
                valueStack.pop();
                number leftOperand = valueStack.top();
                valueStack.pop();

                if (value == "+") {
                    valueStack.push(leftOperand + rightOperand);
                }
                else if (value == "-") {
                    valueStack.push(leftOperand - rightOperand);
                }
                else if (value == "*") {
                    valueStack.push(leftOperand * rightOperand);
                }
                else if (value == "/") {
                    if (rightOperand == 0) {
                        throw std::runtime_error("Деление на ноль");
                    }
                    valueStack.push(leftOperand / rightOperand);
                }
                else if (value == "^") {
                    valueStack.push(std::pow(leftOperand, rightOperand)); // Возведение в степень
                }
            }
            else if (value == "sin" || value == "cos") {
                if (valueStack.empty()) {
                    throw std::runtime_error("Недостаточно операндов для выполнения унарной операции");
                }

                number operand = valueStack.top();
                valueStack.pop();

                if (value == "sin") {
                    valueStack.push(std::sin(operand));
                }
                else if (value == "cos") {
                    valueStack.push(std::cos(operand));
                }
            }
            else {
                throw std::runtime_error("Неизвестный оператор: " + value);
            }
        }
    }

    if (valueStack.getSize() != 1) {
        throw std::runtime_error("Ошибка: некорректное выражение");
    }

    return valueStack.top(); // Возвращаем результат вычисления
}

// Остальные функции остаются без изменений



// Печать инфиксного выражения
void SortingStation::showInf(std::ostream& output) const 
{
    if (!tokensInf.empty()) {
        for (const auto& p : tokensInf) {
            output << p.second << ' ';
        }
        output << '\n';
    }
    else {
        output << "Выражение в инфиксной форме отсутствует\n";
    }
}

// Печать постфиксного выражения
void SortingStation::showPost(std::ostream& output) const 
{
    if (!tokensPost.empty()) {
        for (const auto& p : tokensPost) {
            output << p.second << ' ';
        }
        output << '\n';
    }
    else {
        output << "Выражение в постфиксной форме отсутствует\n";
    }
}