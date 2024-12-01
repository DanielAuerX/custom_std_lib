
#include <iostream>
#include <stdexcept>
#include "logging.hpp"

namespace clib
{
    clib::Log &logger = clib::Log::get_instance();

    template <typename T>
    LinkedList<T>::LinkedList()
    {
        mLength = 0;
        mHead = nullptr;
        logger.log(LogLevel::DEBUG, "instantiating new LinkedList");
            logger.log(LogLevel::DEBUG, "current length: " + std::to_string(mLength));
    }

    template <typename T>
    LinkedList<T>::~LinkedList()
    {
        logger.log(LogLevel::DEBUG, "Calling destructor");
        while (mHead)
        {
            pop_front(); // delete head
        }
        mHead = nullptr;
    }

    /* before:              Head > [10] > [20] > nullptr
                            push_front(5)
        after:              Head > [5] > [10] > [20] > nullptr
    */
    template <typename T>
    void LinkedList<T>::push_front(const T &aData)
    {
        Node *lNode = new Node(aData);
        lNode->next = mHead;
        mHead = lNode;
        mLength++;
        logger.log(LogLevel::DEBUG, "pushed front: " + std::to_string(aData) +
                                        "; new head at: " + clib::pointer_to_string(lNode) +
                                        ", current length: " + std::to_string(mLength));
    }

    template <typename T>
    void LinkedList<T>::push_back(const T &aData)
    {
        if (mHead == nullptr)
        {
            logger.log(LogLevel::DEBUG, "the list is empty. Adding first node");
            push_front(aData);
            return;
        }
        Node *lNode = new Node(aData);
        Node *lBack = get_back();
        lBack->next = lNode;
        mLength++;
        logger.log(LogLevel::DEBUG, "pushed back: " + std::to_string(aData) +
                                        "; new node at: " + clib::pointer_to_string(lNode) +
                                        ", current length: " + std::to_string(mLength));
    }

    /*
    before:             Head → [10] → [20] → [30] → nullptr
                        pop_front()
    after:              Head → [20] → [30] → nullptr
    */
    template <typename T>
    void LinkedList<T>::pop_front()
    {
        if (mHead == nullptr)
        {
            logger.log(LogLevel::WARNING, "the list is empty. cannot pop the front");
            return;
        }
        Node *lTemp = mHead;
        mHead = mHead->next;
        delete lTemp;
        mLength--;
        logger.log(LogLevel::DEBUG, "popping front; deleting node at: " + clib::pointer_to_string(lTemp) +
                                        ", new head at: " +
                                        clib::pointer_to_string(mHead));
        if (mLength == 0)
        {
            mHead = nullptr;
            logger.log(LogLevel::DEBUG, "the list is now empty");
        }
    }

    template <typename T>
    void LinkedList<T>::pop_back()
    {
        if (mHead == nullptr)
        {
            logger.log(LogLevel::WARNING, "the list is empty. Cannot pop the back");
            return;
        }
        Node *lTemp = mHead;
        Node *lBack = mHead;
        while (lBack->next != nullptr)
        {
            lTemp = lBack;
            lBack = lBack->next;
        }
        lTemp->next = nullptr;
        delete lBack;
        mLength--;
        logger.log(LogLevel::DEBUG, "popping back; deleting node at: " + clib::pointer_to_string(lBack) +
                                        ", new length: " + std::to_string(mLength));
        if (mLength == 0)
        {
            mHead = nullptr;
            logger.log(LogLevel::DEBUG, "The list is now empty");
        }
    }

    template <typename T>
    size_t LinkedList<T>::size() const
    {
        return mLength;
    };

    template <typename T>
    T LinkedList<T>::front() const
    {
        if (mHead == nullptr)
        {
            throw std::out_of_range("List is empty");
        }
        return mHead->data;
    }

    template <typename T>
    T LinkedList<T>::back() const
    {
        if (mHead == nullptr)
        {
            throw std::out_of_range("list is empty");
        }

        Node *lBack = get_back();

        return lBack->data;
    }

    template <typename T>
    typename LinkedList<T>::Node *LinkedList<T>::get_back() const
    {
        if (mHead == nullptr)
        {
            return nullptr;
        }
        Node *lBack = mHead;
        while (lBack->next != nullptr)
        {
            lBack = lBack->next;
        }
        return lBack;
    };

}