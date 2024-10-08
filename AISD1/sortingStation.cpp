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
    clear();

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

std::string SortingStation::wrapIfNeeded(const std::string& expression, const std::string& operatorSymbol, bool isLeft) {
    // Извлекаем оператор из выражения (если оно уже содержит оператор)
    std::string innerOp;
    size_t firstSpace = expression.find(' ');
    if (firstSpace != std::string::npos) {
        innerOp = expression.substr(firstSpace + 1, 1); // извлекаем оператор из выражения
    }

    // Если оператор отсутствует, просто возвращаем исходное выражение без скобок
    if (innerOp.empty()) {
        return expression;
    }

    // Проверяем приоритет текущего оператора и оператора в подвыражении
    int currentPrecedence = getPrecedence(operatorSymbol);
    int innerPrecedence = getPrecedence(innerOp);

    // Если приоритет внутреннего оператора меньше, нужны скобки
    if (currentPrecedence > innerPrecedence) {
        return "(" + expression + ")";
    }
    // Если приоритет равен и оператор является правоассоциативным, тоже нужны скобки
    if (currentPrecedence == innerPrecedence && (!isLeft || !isLeftAssociative(operatorSymbol))) {
        return "(" + expression + ")";
    }

    // В других случаях скобки не нужны
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
            tokensPost.push_back(token); // Операнд сразу добавляем в постфиксную запись
        }
        else if (type == "operator") {
            if (value == "(") {
                operatorStack.push(token); // Скобку "(" добавляем в стек
            }
            else if (value == ")") {
                // Убираем операторы из стека до тех пор, пока не найдем "("
                while (!operatorStack.empty() && operatorStack.top().second != "(") {
                    tokensPost.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                // Убираем саму "("
                if (!operatorStack.empty() && operatorStack.top().second == "(") {
                    operatorStack.pop();
                }
            }
            // Обрабатываем унарные операторы, такие как sin и cos
            else if (value == "sin" || value == "cos") {
                operatorStack.push(token); // Унарный оператор сразу помещаем в стек
            }
            else {
                // Проверяем приоритет текущего оператора и операторов в стеке
                while (!operatorStack.empty() &&
                    operatorStack.top().second != "(" && // Не трогаем "("
                    (getPrecedence(operatorStack.top().second) > getPrecedence(value) ||
                        (getPrecedence(operatorStack.top().second) == getPrecedence(value) && isLeftAssociative(value)))) {
                    tokensPost.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token); // Добавляем оператор в стек
            }
        }
    }

    // Опустошаем стек
    while (!operatorStack.empty()) {
        tokensPost.push_back(operatorStack.top());
        operatorStack.pop();
    }
}


// Преобразование постфиксной записи в инфиксную
void SortingStation::postToInf() 
{
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

            std::string leftExpr = wrapIfNeeded(leftOperand, value, true);
            std::string rightExpr = wrapIfNeeded(rightOperand, value, false);

            std::string newExpr = leftExpr + " " + value + " " + rightExpr;
            expressionStack.push(newExpr);
        }
    }

    if (expressionStack.getSize() != 1) {
        throw std::runtime_error("Ошибка преобразования: стек не содержит одно итоговое выражение");
    }

    tokensInf.emplace_back("value", expressionStack.top());
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
            // Обрабатываем бинарные операторы
            if (value == "+" || value == "-" || value == "*" || value == "/" || value == "^") {
                if (valueStack.getSize() < 2) {
                    throw std::runtime_error("Недостаточно операндов для выполнения бинарной операции");
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
            // Обрабатываем унарные операторы
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