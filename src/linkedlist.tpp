
#include <iostream>
#include <stdexcept>

namespace clib
{

    template <typename T>
    LinkedList<T>::LinkedList()
    {
        mLength = 0;
        mHead = nullptr;
        std::cout << "instantiating new LinkedList" << "\n";
        std::cout << "current length: " << mLength << "\n";
    }

    template <typename T>
    LinkedList<T>::~LinkedList()
    {
        std::cout << "calling destructor\n";
        while (mHead)
        {
            pop_front(); // delete head
        }
        mHead = nullptr;
    }

    /* before:              Head → [10] → [20] → nullptr
                            push_front(5)
        after:              Head → [5] → [10] → [20] → nullptr
    */
    template <typename T>
    void LinkedList<T>::push_front(const T &aData)
    {
        Node *lNode = new Node(aData);
        lNode->next = mHead;
        mHead = lNode;
        mLength++;
        std::cout << "pushed front: " << aData << "; new head at: " << lNode
                  << ", current length: " << mLength << "\n";
    }

    template <typename T>
    void LinkedList<T>::push_back(const T &aData)
    {
        if (mHead == nullptr)
        {
            std::cout << "the list is empty. Adding first node\n";
            push_front(aData);
            return;
        }
        Node *lNode = new Node(aData);
        Node *lBack = get_back();
        lBack->next = lNode;
        mLength++;
        std::cout << "pushed back: " << aData << "; new head at: " << lNode
                  << ", current length: " << mLength << "\n";
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
            std::cout << "the list is empty. Cannot pop the front\n";
            return;
        }
        Node *lTemp = mHead;
        mHead = mHead->next;
        delete lTemp;
        mLength--;
        std::cout << "popping front; deleting node at: " << lTemp
                  << ", new head at: " << mHead << "\n";
        if (mLength == 0)
        {
            mHead = nullptr;
            std::cout << "the list is now empty.\n";
        }
    }

    template <typename T>
    void LinkedList<T>::pop_back()
    {
        if (mHead == nullptr)
        {
            std::cout << "the list is empty. Cannot pop the front\n";
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
        std::cout << "popping back; deleting node at: " << lBack
                  << ", new length: " << mLength << "\n";
        if (mLength == 0)
        {
            mHead = nullptr;
            std::cout << "the list is now empty.\n";
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