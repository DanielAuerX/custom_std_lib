#pragma once

#include <cstddef>
#include <iostream>

/*  in c++, std vector == arraylist
    in java, vector (synchronized, thread safe) != arraylist (not thread safe)
*/
namespace clib
{

    enum Order
    {
        ASC,
        DESC
    };

    enum SortType
    {
        MERGE_SORT,
        BUBBLE_SORT
    };

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
        bool contains(const T &value);
        void sort();
        void sort(const Order &order, const SortType &sortType);
        // TODO: removeAtIndex

    private:
        void mergeAsc(T inputArray[], T left[], size_t leftSize, T right[], size_t rightSize);
        void mergeDesc(T inputArray[], T left[], size_t leftSize, T right[], size_t rightSize);
        void merge_sort(T inputArray[], size_t inputLength, const Order &order);
        void bubble_sort(T inputArray[], const size_t &inputLength, const Order &order);
        bool isBigger(const T i, const T j, const Order &order);
        int binary_search(const T sortedInputArray[], const size_t &inputLength, const T &target);

        void resize();
        T *array;
        size_t capacity;
        size_t length;
    };

}

#include "../src/arraylist.tpp"