#pragma once

#include <cstddef>
#include <iostream>

/*  in c++, std vector == arraylist
    in java, vector (synchronized, thread safe) != arraylist (not thread safe)
*/
namespace clib
{
    template <typename T>
    class ArrayList
    {
    public:
        ArrayList(size_t size);
        ~ArrayList();

        void push_back(const T &value);
        void pop_back();
        T &operator[](size_t index) const;
        size_t size() const;
        void sort();
        // TODO: removeAtIndex

    private:
        void merge(T inputArray[], T left[], size_t leftSize, T right[], size_t rightSize);
        void merge_sort(T inputArray[], size_t inputLength);
        void resize();
        T *array;
        size_t capacity;
        size_t length;
    };

}

#include "../src/arraylist.tpp"