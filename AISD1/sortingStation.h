#ifndef SORTINGSTATION_H
#define SORTINGSTATION_H

#include <vector>
#include <string>
#include <iostream>

typedef double number;

class SortingStation
{
private:
    std::vector<std::pair<std::string, std::string>> tokensInf;
    std::vector<std::pair<std::string, std::string>> tokensPost;

public:
    SortingStation();
    ~SortingStation();

    int getPrecedence(const std::string& op);
    bool isLeftAssociative(const std::string& op);
    std::string wrapIfNeeded(const std::string& expression, const std::string& operatorSymbol, bool isLeft);

    bool tokenize(const std::string& input, bool isInf = true);
    void infToPost();
    void postToInf();
    number evaluatePost();
    void showInf(std::ostream& output) const;
    void showPost(std::ostream& output) const;

    void clear();
};

#endif
