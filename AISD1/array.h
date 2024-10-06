#ifndef ARRAY_H
#define ARRAY_H

#include <algorithm>
#include <stdexcept>
#include <cstddef>

template <typename T>
class Array
{
private:
    T* data;
    size_t capacity;
    size_t size;

public:
    Array();
    Array(const Array<T>& other);
    Array<T>& operator=(const Array<T>& other);
    ~Array();

    void resize(size_t newCapacity);

    void push_back(const T& value);
    void pop_back();
    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    size_t getSize() const;
    bool empty() const;
    size_t getCapacity() const;
    void insert(size_t index, const T& value);
    void erase(size_t index);
    void sort();

    void clear();

    void print(std::ostream& os) const;
};

// ����������� �� ���������
template <typename T>
Array<T>::Array() : data(nullptr), capacity(0), size(0) {}

// ����������� �����������
template <typename T>
Array<T>::Array(const Array<T>& other) : data(nullptr), capacity(0), size(0) {
    if (other.size > 0) {
        resize(other.capacity);
        for (size_t i = 0; i < other.size; ++i) {
            data[i] = other.data[i];
        }
        size = other.size;
    }
}

// �������� ������������
template <typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) 
{
    if (this != &other) {
        delete[] data;

        if (other.size > 0) {
            resize(other.capacity);
            for (size_t i = 0; i < other.size; ++i) {
                data[i] = other.data[i];
            }
            size = other.size;
        }
        else {
            data = nullptr;
            capacity = 0;
            size = 0;
        }
    }

    return *this;
}

// ����������
template <typename T>
Array<T>::~Array() 
{
    delete[] data;
}

// ����� ��� ��������� ������� �������
template <typename T>
void Array<T>::resize(size_t newCapacity) 
{
    T* newData = new T[newCapacity];

    for (size_t i = 0; i < size; ++i) {
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

// ���������� �������� � ����� �������
template <typename T>
void Array<T>::push_back(const T& value) 
{
    if (size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[size++] = value;
}

// �������� ���������� �������� �������
template <typename T>
void Array<T>::pop_back() 
{
    if (size == 0) {
        throw std::out_of_range("Array is empty!");
    }
    --size;
}

// �������� ��� ������� � �������� �� �������
template <typename T>
T& Array<T>::operator[](size_t index) 
{
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

// ����������� �������� ��� ������� � �������� �� �������
template <typename T>
const T& Array<T>::operator[](size_t index) const 
{
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    return data[index];
}

// ��������� �������� ������� �������
template <typename T>
size_t Array<T>::getSize() const 
{
    return size;
}

// �������� �� ������� �������
template <typename T>
bool Array<T>::empty() const 
{
    return size == 0;
}

// ��������� ������� �������
template <typename T>
size_t Array<T>::getCapacity() const 
{
    return capacity;
}

// ������� �������� � �������� �������
template <typename T>
void Array<T>::insert(size_t index, const T& value) 
{
    if (index > size) {
        throw std::out_of_range("Index out of bounds");
    }
    if (size == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    for (size_t i = size; i > index; --i) {
        data[i] = data[i - 1];
    }
    data[index] = value;
    size++;
}

// �������� �������� �� �������
template <typename T>
void Array<T>::erase(size_t index) 
{
    if (index >= size) {
        throw std::out_of_range("Index out of bounds");
    }
    for (size_t i = index; i < size - 1; ++i) {
        data[i] = data[i + 1];
    }
    --size;
}

// ���������� �������
template <typename T>
void Array<T>::sort() 
{
    if (size > 1) {
        std::sort(data, data + size);
    }
}

template <typename T>
void Array<T>::clear() 
{
    delete[] data;
    data = nullptr;
    size = 0;
    capacity = 0;
}

// ������� ������ �������
template <typename T>
void Array<T>::print(std::ostream& os) const 
{
    for (size_t i = 0; i < size; ++i) {
        os << data[i] << " ";  // ������� ������ ������� �������
    }
    os << std::endl;  // ��������� �� ����� ������
}

#endif