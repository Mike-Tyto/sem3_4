#pragma once
#include <stddef.h>
#include <exception>
#include <iostream>

template <typename T>
class DynamicArray {
private:
    T *arr; // указатель на массив
    size_t size; // текущий размер массива

public:
    // конструктор
    DynamicArray() {
        this->size = 0;
        this->arr = new T[1];
    }

    DynamicArray(size_t size) {
        this->size = size;
        this->arr = new T[size];
        for (int i = 0; i < size; i++) {
            arr[i] = T();
        }
    }

    DynamicArray(T* items, size_t size) {
        this->size = size;
        this->arr = new T[size];
        for (int i = 0; i < size; i++) {
            arr[i] = items[i];
        }
    }

    DynamicArray(const DynamicArray<T>& dynamicArray) {
        this->size = dynamicArray.size;
        this->arr = new T[size];
        for (int i = 0; i < size; i++) {
            arr[i] = dynamicArray.arr[i];
        }
    }

    DynamicArray(DynamicArray<T>&& dynamicArray) {
        this->size = dynamicArray.size;
        this->arr = dynamicArray.arr;
        dynamicArray.size = 0;
        dynamicArray.arr = nullptr;
    }

   template <typename... Args>
   DynamicArray(T head, Args... args) {
       arr = new T[sizeof...(args) + 1];
       arr[0] = head;

       size = sizeof...(args) + 1;

       size_t i = 1;
       ((arr[i++] = args), ...);
   }

    // деструктор
    ~DynamicArray() {
        delete[] arr;
    }

    class Iterator {
    private:
        T* ptr;
    public:
        Iterator(T* ptr) {
            this->ptr = ptr;
        }
        T& operator*() {
            return *ptr;
        }
        Iterator& operator++() {
            ptr++;
            return *this;
        }
        bool operator!=(const Iterator& other) {
            return ptr != other.ptr;
        }
    };

    Iterator begin() {
        return Iterator(arr);
    }

    Iterator end() {
        return Iterator(arr + size);
    }

    // Изменение размера массива
    void Resize(size_t newSize) {
        if (newSize < 0) {
            throw std::invalid_argument("new size was less than zero");
        }

        T* newBlock = new T[newSize];

        // for (size_t i = 0; i < newSize; i++) {
        //     newBlock[i] = T();
        // }

        if (newSize < size) {
            for (size_t i = 0; i < newSize; i++)
                newBlock[i] = this->Get(i);
        }
        else {
            for (size_t i = 0; i < size; i++)
                newBlock[i] = this->Get(i);
        }

        if (arr)
            delete[] arr;

        arr = newBlock;
        size = newSize;
    }

    // метод получения элемента по индексу
    T& Get(int index) const {
        if (index >= size || index < 0) {
            throw std::out_of_range("Index out of range");
        }
        return arr[index];
    }

    // метод изменения элемента по индексу
    void Set(int index, T element) {
        if (index >= size || index < 0) {
            throw std::out_of_range("Index out of range");
        }
        arr[index] = element;
    }

    // метод получения текущего размера массива
    int GetSize() const noexcept {
        return size;
    }

    friend std::ostream& operator<< (std::ostream& os, const DynamicArray<T>& array) {
        if (array.size == 0) {
            os << "[]";
        }
        else {
            os << "[";

            for (size_t i = 0; i < array.size - 1; i++) {
                os << array.Get(i) << ", ";
            }
            os << array.Get(array.size - 1) << "]";
        }
        return os;
    }

    bool operator== (const DynamicArray<T>& sequence) {
        if (this->size != sequence.GetLength()) {
            return 0;
        }

        for (int i = 0; i < this->size; i++) {
            if (this->Get(i) != sequence.Get(i)) {
                return 0;
            }
        }

        return 1;
    }

    auto& operator[] (const int index) const {
        return Get(index);
    }

    DynamicArray<T>& operator= (const DynamicArray<T>& dynamicArray) {
        if (this == &dynamicArray) {
            return *this;
        }
        delete[] arr;
        this->size = dynamicArray.size;
        this->arr = new T[size];
        for (int i = 0; i < size; i++) {
            arr[i] = dynamicArray.arr[i];
        }
        return *this;
    }

    DynamicArray<T>& operator= (DynamicArray<T>&& dynamicArray) {
        if (this == &dynamicArray) {
            return *this;
        }
        delete[] arr;
        this->size = dynamicArray.size;
        this->arr = dynamicArray.arr;
        dynamicArray.size = 0;
        dynamicArray.arr = nullptr;
        return *this;
    }
};
