#pragma once
#include <iostream>
#include "Sequence.h"

template <class T>
class DynamicArray : public Sequence<T>
{
private:
    T* data;
    int size;
    int capacity;

    void Resize(int newCapacity)
    {
        if (newCapacity < size)
            newCapacity = size;

        T* newData = new T[newCapacity];

        for (int i = 0; i < size; ++i)
        {
            newData[i] = data[i];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

public:
    class DynamicArrayIterator : public Sequence<T>::Iterator {
    private:
        T* current;

    public:
        DynamicArrayIterator(T* current) : current(current) { }

        bool operator==(const typename Sequence<T>::Iterator& other) const override
        {
            const DynamicArrayIterator* otherIterator = dynamic_cast<const DynamicArrayIterator*>(&other);
            return otherIterator && current == otherIterator->current;
        }

        bool operator!=(const typename Sequence<T>::Iterator& other) const override
        {
            return !(*this == other);
        }

        T& operator*() override
        {
            return *current;
        }

        typename Sequence<T>::Iterator& operator++() override
        {
            current++;
            return *this;
        }
    };

    typename Sequence<T>::Iterator* ToBegin() override
    {
        return new DynamicArrayIterator(data);
    }

    typename Sequence<T>::Iterator* ToEnd() override
    {
        return new DynamicArrayIterator(data + size);
    }

    DynamicArray() : size(0), capacity(10) {
        data = new T[capacity];
    }

    DynamicArray(int initialCapacity) : size(0), capacity(initialCapacity) {
        data = new T[capacity];
    }

    DynamicArray(const DynamicArray<T>& dynamicArray)
    {
        size = dynamicArray.size;
        capacity = dynamicArray.capacity;
        data = new T[capacity];

        for (int i = 0; i < size; ++i)
        {
            Set(i, dynamicArray.data[i]);
        }
    }

    DynamicArray(T* items, int itemsSize)
    {
        size = itemsSize;
        capacity = itemsSize * 2;
        data = new T[capacity];

        for (int i = 0; i < size; ++i)
        {
            Set(i, items[i]);
        }
    }

    ~DynamicArray()
    {
        delete[] data;
    }

    T& operator[](int index)
    {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    T& GetFirstElem() override
    {
        if (size == 0)
            throw std::out_of_range("Array is empty");
        return GetElem(0);
    }

    T& GetLastElem() override
    {
        if (size == 0)
            throw std::out_of_range("Array is empty");
        return GetElem(size - 1);
    }

    T& GetElem(int index) override
    {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index]; // Правильный возврат элемента массива
    }

    const T& GetElem(int index) const override
    {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        return data[index]; // Правильный возврат элемента массива
    }

    void Swap(T& a, T& b) override
    {
        T temp = a;
        a = b;
        b = temp;
    }

    void Set(int index, T value) override
    {
        if (index < 0) {
            throw std::out_of_range("Negative index not allowed");
        }

        if (index >= capacity) {
            Resize(index + 1);
        }
        data[index] = value;
        if (index >= size)
            size = index + 1;
    }

    DynamicArray<T>* GetSubsequence(int startIndex, int endIndex) override
    {
        if (startIndex < 0 || endIndex >= size || startIndex > endIndex) {
            throw std::out_of_range("Invalid subsequence indices");
        }

        int length = endIndex - startIndex + 1;
        T* items = new T[length];

        for (int i = 0; i < length; i++)
        {
            items[i] = GetElem(startIndex + i);
        }

        return new DynamicArray<T>(items, length);
    }

    int GetLength() override
    {
        return size;
    }

    int GetLength() const override
    {
        return size;
    }

    void Append(T dataElem) override
    {
        Insert(dataElem, size);
    }

    void Prepend(T dataElem) override
    {
        Insert(dataElem, 0);
    }

    void Insert(T dataElem, int index) override
    {
        if (index < 0 || index > size) {
            throw std::out_of_range("Insert index out of range");
        }

        if (size >= capacity)
            Resize(capacity * 2);

        for (int i = size; i > index; i--)
        {
            Set(i, data[i - 1]);
        }

        Set(index, dataElem);
    }

    void Union(Sequence<T>* dynamicArray) override
    {
        for (int i = 0; i < dynamicArray->GetLength(); i++)
        {
            Append(dynamicArray->GetElem(i));
        }
    }

    void Print() const {
        std::cout << "Elements in the array: ";
        for (int i = 0; i < size; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    void Clear() {
        delete[] data;
        data = new T[capacity];
        size = 0;
    }
};
