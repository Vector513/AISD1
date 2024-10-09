#ifndef LIST_H
#define LIST_H

#include <iostream>

template <typename T>
class List 
{
private:
    struct ListNode {
        T data;
        ListNode* prev;
        ListNode* next;

        ListNode(const T& data, ListNode* prev = nullptr, ListNode* next = nullptr);
    };

    ListNode* head;
    ListNode* tail;
    size_t size;

public:
    List();
    ~List();

    void push_front(const T& data);
    void push_back(const T& data);
    void pop_front();
    void pop_back();

    T front() const;
    T back() const;

    bool empty() const;
    size_t getSize() const;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    void insert(size_t index, const T& data);
    void erase(size_t index);

    void print_forward(std::ostream& os) const;
    void print_backward(std::ostream& os) const;

    void clear();
};


template <typename T>
List<T>::ListNode::ListNode(const T& data, ListNode* prev, ListNode* next)
    : data(data), prev(prev), next(next) {}

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size(0) {}

template <typename T>
List<T>::~List()
{
    clear();
}

template <typename T>
void List<T>::clear() 
{
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }

    tail = nullptr;
    size = 0;
}

template <typename T>
void List<T>::push_front(const T& data)
{
    ListNode* newNode = new ListNode(data, nullptr, head);
    if (head) {
        head->prev = newNode;
    }
    else {
        tail = newNode;
    }
    head = newNode;
    size++;
}

template <typename T>
void List<T>::push_back(const T& data)
{
    ListNode* newNode = new ListNode(data, tail, nullptr);
    if (tail) {
        tail->next = newNode;
    }
    else {
        head = newNode;
    }
    tail = newNode;
    size++;
}

template <typename T>
void List<T>::pop_front()
{
    if (empty()) {
        throw std::out_of_range("List is empty!");
    }
    ListNode* temp = head;
    head = head->next;
    if (head) {
        head->prev = nullptr;
    }
    else {
        tail = nullptr;
    }
    delete temp;
    size--;
}

template <typename T>
void List<T>::pop_back()
{
    if (empty()) {
        throw std::out_of_range("List is empty!");
    }
    ListNode* temp = tail;
    tail = tail->prev;
    if (tail) {
        tail->next = nullptr;
    }
    else {
        head = nullptr;
    }
    delete temp;
    size--;
}

template <typename T>
T List<T>::front() const
{
    if (empty()) {
        throw std::out_of_range("List is empty!");
    }
    return head->data;
}

template <typename T>
T List<T>::back() const
{
    if (empty()) {
        throw std::out_of_range("List is empty!");
    }
    return tail->data;
}

template <typename T>
bool List<T>::empty() const
{
    return size == 0;
}

template <typename T>
size_t List<T>::getSize() const
{
    return size;
}

template <typename T>
T& List<T>::operator[](size_t index) 
{
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    ListNode* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
const T& List<T>::operator[](size_t index) const 
{
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    ListNode* current = head;
    for (size_t i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename T>
void List<T>::insert(size_t index, const T& data) 
{
    if (index > size) {
        throw std::out_of_range("Index out of bounds");
    }
    if (index == 0) {
        push_front(data);
    }
    else if (index == size) {
        push_back(data);
    }
    else {
        if (index < size / 2) {
            ListNode* current = head;
            for (size_t i = 0; i < index; ++i) {
                current = current->next;
            }
            ListNode* newNode = new ListNode(data, current->prev, current);
            current->prev->next = newNode;
            current->prev = newNode;
            size++;
        }
        else {
            ListNode* current = tail;
            for (size_t i = size - 1; i > index; --i) {
                current = current->prev;
            }
            ListNode* newNode = new ListNode(data, current->prev, current);
            current->prev->next = newNode;
            current->prev = newNode;
            size++;
        }
    }
}

template <typename T>
void List<T>::erase(size_t index) 
{
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    if (index == 0) {
        pop_front();
    }
    else if (index == size - 1) {
        pop_back();
    }
    else {
        ListNode* current = head;
        for (size_t i = 0; i < index; ++i) {
            current = current->next;
        }
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        size--;
    }
}

template <typename T>
void List<T>::print_forward(std::ostream& os) const
{
    ListNode* current = head;
    while (current) {
        os << current->data << " ";
        current = current->next;
    }
    os << '\n';
}

template <typename T>
void List<T>::print_backward(std::ostream& os) const
{
    ListNode* current = tail;
    while (current) {
        os << current->data << " ";
        current = current->prev;
    }
    os << '\n';
}

#endif