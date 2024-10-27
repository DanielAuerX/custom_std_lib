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
        T &operator[](size_t index);
        size_t size() const;
        //removeAtIndex

    private:
        void resize();
        T *array;
        size_t capacity;
        size_t length;
    };

}

#include "../src/arraylist.tpp"