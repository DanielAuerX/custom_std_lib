#include "../include/arraylist.hpp"
#include "../include/linkedlist.hpp"
#include "../include/memory_alloc.hpp"
#include "../include/logging.hpp"
#include "../include/unique_pointer.hpp"
#include <iostream>
#include <string>
#include <sstream>

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

std::string pointer_to_string(void *ptr)
{
    std::ostringstream oss;
    oss << ptr;
    return oss.str();
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
    clib::Log &logger = clib::Log::get_instance();

    LinkedList<int> linkedList;
    int first = 5;

    linkedList.push_front(first);

    int second = 99;
    linkedList.push_front(second);

    int newFirst = 2;
    linkedList.push_back(newFirst);

    int anotherNewFirst = 1;
    linkedList.push_back(anotherNewFirst);

    logger.log(clib::LogLevel::INFO, "front value: " + std::to_string(linkedList.front()));
    logger.log(clib::LogLevel::INFO, "back value: " + std::to_string(linkedList.back()));
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

void test_logging()
{
    clib::Log &logger = clib::Log::get_instance();
    // logger.set_log_level(clib::LogLevel::DEBUG);

    logger.log(clib::LogLevel::DEBUG, "DEBUG MESSAGE");
    logger.log(clib::LogLevel::INFO, "INFO MESSAGE");
    logger.log(clib::LogLevel::WARNING, "WARNING");
    logger.log(clib::LogLevel::ERROR, "ERROR MESSAGE");

    const int testInt = 10;
    // logger.log(clib::LogLevel::INFO, "This is a test with variables {}", testInt);
}

void test_unique_pointer()
{
    using namespace clib;

    Log &logger = Log::get_instance();

    UniquePtr<int> uniqueInt(new int(42));

    //std::string msg = "unique pointer value" + std::to_string(uniqueInt.get()); 
    logger.log(LogLevel::INFO, "unique pointer value (using get): " + std::to_string(*uniqueInt.get()));

    uniqueInt.reset(new int(99)); // different value
    logger.log(LogLevel::INFO, "value after reset: " + std::to_string(*uniqueInt));

    // no argument -> set to nullptr
    uniqueInt.reset();
    if (uniqueInt.get() == nullptr) {
        logger.log(LogLevel::INFO, "pointer set to nullptr");
    } else {
        logger.log(LogLevel::ERROR, "failed to reset");
    }

    UniquePtr<std::string> uniqueString(new std::string("test string"));
    logger.log(LogLevel::INFO, "string value (using * operator): " + *uniqueString);
    logger.log(LogLevel::INFO, "string length (using -> operator): " + std::to_string(uniqueString->length()));

    std::string *rawPtr = uniqueString.release();
    if (uniqueString.get() == nullptr) {
        logger.log(LogLevel::INFO, "tes release: successful");
    } else {
        logger.log(LogLevel::ERROR, "tes release: failed");
    }

    logger.log(LogLevel::INFO, "raw pointer value (released pointer): " + *rawPtr);
    delete rawPtr;

}

int main()
{
    test_unique_pointer();

    // testMemoryAlloc();
    // testLinkedList();
    // testArrayList();
    // test_logging();
    // std::cout << "final memory usage: " << get_memory_usage() << "\n";
    return 0;
}