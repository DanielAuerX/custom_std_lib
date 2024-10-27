#pragma once

/*
linked list: dynamically sized, because it saves items wherever there is available memory space
*/
namespace clib
{

    template <typename T>
    class LinkedList
    {
    public:
        LinkedList();
        ~LinkedList();
        void push_front(const T &aData);
        void pop_front();
        void push_back(const T &aData);
        void pop_back();
        size_t size() const;
        T front() const;
        T back() const;

    private:
        struct Node
        {
            T data;
            Node *next;
            Node(const T &value) : data(value), next(nullptr) {}
        };

        Node *mHead;
        size_t mLength;

        Node *get_back() const;
    };

}
#include "../src/linkedlist.tpp"