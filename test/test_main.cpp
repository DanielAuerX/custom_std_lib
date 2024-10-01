#include "../include/arraylist.hpp"
#include <iostream>

using namespace lists;

int main()
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

    //intList[40];

    intList.push_back(99);
    std::cout << "size of array: " << intList.size() << std::endl;

    return 0;
}