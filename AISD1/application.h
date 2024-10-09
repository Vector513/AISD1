#ifndef APPLICATION_H
#define APPLICATION_H

#include "list.h"
#include "array.h"
#include "stack.h"
#include "sortingStation.h"

class Application
{
private:
    List<number> list;
    Array<number> array;
    Stack<number> stack;
    SortingStation station;

public:
    Application();
    ~Application();

    bool getValidInput(number& value);
    bool getValidInput(size_t& value);
    bool getValidInputWithIndex(number& n, size_t& i);
    bool getValidInputWithIndex(size_t& i1, size_t& i2);

    void run();
};

#endif