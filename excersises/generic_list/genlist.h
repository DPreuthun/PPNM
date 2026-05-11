#ifndef GENLIST_H
#define GENLIST_H

#include <iostream>
#include <cassert>

template <typename T>
class genlist {

private:
    T* data;
    int size;
    int capacity;

    void resize() {

        capacity *= 2;

        T* new_data = new T[capacity];

        for (int i = 0; i < size; i++) {
            new_data[i] = data[i];
        }

        delete[] data;

        data = new_data;
    }

public:

    genlist() {

        size = 0;
        capacity = 2;

        data = new T[capacity];
    }

    ~genlist() {
        delete[] data;
    }

    void add(const T& item) {

        if (size >= capacity) {
            resize();
        }

        data[size] = item;
        size++;
    }

    void remove(int index) {

        assert(index >= 0 && index < size);

        for (int i = index; i < size - 1; i++) {
            data[i] = data[i + 1];
        }

        size--;
    }

    T& operator[](int index) {

        assert(index >= 0 && index < size);

        return data[index];
    }

    const T& operator[](int index) const {

        assert(index >= 0 && index < size);

        return data[index];
    }

    int getSize() const {
        return size;
    }
};

#endif