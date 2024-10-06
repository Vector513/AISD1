#ifndef STACK_H
#define STACK_H

template <typename T>
class Stack 
{
private:
    struct ListNode {
        T data;
        ListNode* next;

        ListNode(const T& data, ListNode* next = nullptr) : data(data), next(next) {}
    };

    ListNode* topNode;
    size_t size;

public:
    Stack();
    ~Stack();

    Stack<T>& operator=(const Stack<T>& other);
    Stack(const Stack<T>& other);

    void push(const T& value);
    void pop();

    T& top();
    const T& top() const;

    bool empty() const;
    size_t getSize() const;

    void clear();

    void print(std::ostream& os) const;
};

template <typename T>
Stack<T>::Stack() : topNode(nullptr), size(0) {}

template <typename T>
Stack<T>::~Stack()
{
    clear();
}

template <typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& other)
{
    if (this == &other) {
        return *this;
    }

    clear();

    if (other.topNode != nullptr) {
        ListNode* current = other.topNode;
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
    }

    return *this;
}

template <typename T>
Stack<T>::Stack(const Stack<T>& other) : topNode(nullptr), size(0)
{
    *this = other;
}

template <typename T>
void Stack<T>::push(const T& value)
{
    topNode = new ListNode(value, topNode);
    ++size;
}

template <typename T>
void Stack<T>::pop()
{
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }

    ListNode* temp = topNode;
    topNode = topNode->next;
    delete temp;
    --size;
}

template <typename T>
T& Stack<T>::top()
{
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return topNode->data;
}

template <typename T>
const T& Stack<T>::top() const
{
    if (empty()) {
        throw std::out_of_range("Stack is empty");
    }
    return topNode->data;
}

template <typename T>
bool Stack<T>::empty() const
{
    return topNode == nullptr;
}

template <typename T>
size_t Stack<T>::getSize() const
{
    return size;
}

template <typename T>
void Stack<T>::clear() 
{
    while (!empty()) {
        pop();
    }
}

template <typename T>
void Stack<T>::print(std::ostream& os) const 
{
    ListNode* current = topNode;
    while (current != nullptr) {
        os << current->data << " ";
        current = current->next;
    }
    os << '\n';
}

#endif
