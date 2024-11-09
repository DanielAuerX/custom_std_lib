#include "../include/arraylist.hpp"
#include "../include/linkedlist.hpp"
#include "../include/memory_alloc.hpp"
#include <iostream>

using namespace clib;

void testArrayList()
{
    ArrayList<int> intList(5);

    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(100);

    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(99);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(99);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(99);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(99);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(99);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(99);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.pop_back();

    size_t index = 0;
    int integer = intList[index];
    std::cout << "value of index " << index << " is " << integer << std::endl;

    // intList[40];

    intList.push_back(99);
    std::cout << "size of array: " << intList.size() << std::endl;
}

void testLinkedList()
{
    LinkedList<int> linkedList;
    int first = 5;

    linkedList.push_front(first);

    int second = 99;
    linkedList.push_front(second);

    int newFirst = 2;
    linkedList.push_back(newFirst);

    int anotherNewFirst = 1;
    linkedList.push_back(anotherNewFirst);

    std::cout << "front value: " << linkedList.front() << "\n";
    std::cout << "back value: " << linkedList.back() << "\n";
}

void testMemoryAlloc()
{
    std::cout << "initial memory usage: " << get_memory_usage()  << "\n";

    int *intPtr = new int(42);

    int *intArray = new int[10];

    delete intPtr;

    delete[] intArray;
    std::cout << "final memory usage: " << get_memory_usage() << "\n";
}

int main()
{
    //testMemoryAlloc();
    testLinkedList();
    // testArrayList();

    return 0;
}