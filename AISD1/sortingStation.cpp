#include "sortingStation.h"
#include "stack.h"
#include <sstream>
#include <cctype>
#include <cmath>
#include <iostream>

SortingStation::SortingStation() : tokensInf(), tokensPost() {}

SortingStation::~SortingStation() {}

// ������� ������� ������� ����� ����� ����������
void SortingStation::clear() {
    tokensInf.clear();
    tokensPost.clear();
}

// ����������� ������ � ��������� ��� ����������� ������
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
                std::cerr << "������: ������������ ������ '" << c << "' � ���������.\n";
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
        std::cerr << "������: ������������ ���������� ���������� � ���������.\n";
        clear();
        return false;
    }

    if (openBrackets != closeBrackets) {
        std::cerr << "������: ������������ ���������� ������.\n";
        clear();
        return false;
    }
    return true;
}

// ������� ��� ��������� ���������� ���������
int SortingStation::getPrecedence(const std::string& op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 0;
}

// ������� ��� �������� ��������������� ���������
bool SortingStation::isLeftAssociative(const std::string& op) {
    return op != "^";
}

std::string SortingStation::wrapIfNeeded(const std::string& expression, const std::string& operatorSymbol, bool isLeft) {
    // ��������� �������� �� ��������� (���� ��� ��� �������� ��������)
    std::string innerOp;
    size_t firstSpace = expression.find(' ');
    if (firstSpace != std::string::npos) {
        innerOp = expression.substr(firstSpace + 1, 1); // ��������� �������� �� ���������
    }

    // ���� �������� �����������, ������ ���������� �������� ��������� ��� ������
    if (innerOp.empty()) {
        return expression;
    }

    // ��������� ��������� �������� ��������� � ��������� � ������������
    int currentPrecedence = getPrecedence(operatorSymbol);
    int innerPrecedence = getPrecedence(innerOp);

    // ���� ��������� ����������� ��������� ������, ����� ������
    if (currentPrecedence > innerPrecedence) {
        return "(" + expression + ")";
    }
    // ���� ��������� ����� � �������� �������� ������������������, ���� ����� ������
    if (currentPrecedence == innerPrecedence && (!isLeft || !isLeftAssociative(operatorSymbol))) {
        return "(" + expression + ")";
    }

    // � ������ ������� ������ �� �����
    return expression;
}


// �������������� ��������� ������ � �����������
void SortingStation::infToPost() {
    tokensPost.clear();
    Stack<std::pair<std::string, std::string>> operatorStack;

    for (const auto& token : tokensInf) {
        const std::string& type = token.first;
        const std::string& value = token.second;

        if (type == "value") {
            tokensPost.push_back(token); // ������� ����� ��������� � ����������� ������
        }
        else if (type == "operator") {
            if (value == "(") {
                operatorStack.push(token); // ������ "(" ��������� � ����
            }
            else if (value == ")") {
                // ������� ��������� �� ����� �� ��� ���, ���� �� ������ "("
                while (!operatorStack.empty() && operatorStack.top().second != "(") {
                    tokensPost.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                // ������� ���� "("
                if (!operatorStack.empty() && operatorStack.top().second == "(") {
                    operatorStack.pop();
                }
            }
            // ������������ ������� ���������, ����� ��� sin � cos
            else if (value == "sin" || value == "cos") {
                operatorStack.push(token); // ������� �������� ����� �������� � ����
            }
            else {
                // ��������� ��������� �������� ��������� � ���������� � �����
                while (!operatorStack.empty() &&
                    operatorStack.top().second != "(" && // �� ������� "("
                    (getPrecedence(operatorStack.top().second) > getPrecedence(value) ||
                        (getPrecedence(operatorStack.top().second) == getPrecedence(value) && isLeftAssociative(value)))) {
                    tokensPost.push_back(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token); // ��������� �������� � ����
            }
        }
    }

    // ���������� ����
    while (!operatorStack.empty()) {
        tokensPost.push_back(operatorStack.top());
        operatorStack.pop();
    }
}


// �������������� ����������� ������ � ���������
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
                throw std::runtime_error("������������ ��������� ��� ���������");
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
        throw std::runtime_error("������ ��������������: ���� �� �������� ���� �������� ���������");
    }

    tokensInf.emplace_back("value", expressionStack.top());
}


// ���������� ��������� � ����������� ������
number SortingStation::evaluatePost() {
    Stack<number> valueStack;

    for (const auto& token : tokensPost) {
        const std::string& type = token.first;
        const std::string& value = token.second;

        if (type == "value") {
            valueStack.push(std::stod(value)); // ����������� ������ � �����
        }
        else if (type == "operator") {
            // ������������ �������� ���������
            if (value == "+" || value == "-" || value == "*" || value == "/" || value == "^") {
                if (valueStack.getSize() < 2) {
                    throw std::runtime_error("������������ ��������� ��� ���������� �������� ��������");
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
                        throw std::runtime_error("������� �� ����");
                    }
                    valueStack.push(leftOperand / rightOperand);
                }
                else if (value == "^") {
                    valueStack.push(std::pow(leftOperand, rightOperand)); // ���������� � �������
                }
            }
            // ������������ ������� ���������
            else if (value == "sin" || value == "cos") {
                if (valueStack.empty()) {
                    throw std::runtime_error("������������ ��������� ��� ���������� ������� ��������");
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
                throw std::runtime_error("����������� ��������: " + value);
            }
        }
    }

    if (valueStack.getSize() != 1) {
        throw std::runtime_error("������: ������������ ���������");
    }

    return valueStack.top(); // ���������� ��������� ����������
}


// ������ ���������� ���������
void SortingStation::showInf(std::ostream& output) const 
{
    if (!tokensInf.empty()) {
        for (const auto& p : tokensInf) {
            output << p.second << ' ';
        }
        output << '\n';
    }
    else {
        output << "��������� � ��������� ����� �����������\n";
    }
}

// ������ ������������ ���������
void SortingStation::showPost(std::ostream& output) const 
{
    if (!tokensPost.empty()) {
        for (const auto& p : tokensPost) {
            output << p.second << ' ';
        }
        output << '\n';
    }
    else {
        output << "��������� � ����������� ����� �����������\n";
    }
}