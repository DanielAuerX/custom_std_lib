#include "../include/arraylist.hpp"
#include "../include/linkedlist.hpp"
#include "../include/memory_alloc.hpp"
#include <iostream>

using namespace clib;

void printContentArrayList(const ArrayList<int> &arrayList, const std::string &tag)
{
    std::string result = tag + ": ";
    for (size_t i = 0; i < arrayList.size(); ++i)
    {
        result += std::to_string(arrayList[i]);
        if (i < arrayList.size() - 1)
        {
            result += ", ";
        }
    }
    std::cout << result << "\n";
}

void testArrayList()
{
    ArrayList<int> intList(5);

    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(100);

    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(2);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(9);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(99);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(73);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(1);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.push_back(-1);
    std::cout << "size of array: " << intList.size() << std::endl;

    intList.pop_back();

    size_t index = 0;
    int integer = intList[index];
    std::cout << "value of index " << index << " is " << integer << std::endl;

    // intList[40];

    intList.push_back(99);
    std::cout << "size of array: " << intList.size() << std::endl;

    bool contains = intList.contains(73);
    std::cout
        << "the arraylist contains 73: " << contains << std::endl;
    
    contains = intList.contains(10);
    std::cout << "the arraylist contains 10: " << contains << std::endl;

    printContentArrayList(intList, "before");
    intList.sort(Order::ASC, SortType::MERGE_SORT);
    printContentArrayList(intList, "after");
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
    std::cout << "initial memory usage: " << get_memory_usage() << "\n";

    int *intPtr = new int(42);

    int *intArray = new int[10];

    delete intPtr;

    delete[] intArray;
    std::cout << "final memory usage: " << get_memory_usage() << "\n";
}

int main()
{
    // testMemoryAlloc();
    // testLinkedList();
    testArrayList();

    return 0;
}