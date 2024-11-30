#include "memory_alloc.hpp"
#include <map>
#include <stdexcept>

size_t total_allocated_memory = 0;
std::map<void *, size_t> allocated_array_memory;
clib::Log &logger = clib::Log::get_instance();

size_t get_memory_usage()
{
    return total_allocated_memory;
}

void add_allocation(void *ptr, size_t size)
{
    allocated_array_memory[ptr] = size;
}

void remove_allocation(void *ptr)
{
    auto it = allocated_array_memory.find(ptr);
    if (it != allocated_array_memory.end())
    {
        size_t size = it->second;
        allocated_array_memory.erase(it);
    }
}

size_t get_size(void *ptr)
{
    auto it = allocated_array_memory.find(ptr);
    if (it != allocated_array_memory.end())
    {
        return it->second;
    }
    throw std::runtime_error("cannot find address in allocated memory");
}

void *operator new(std::size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        throw std::bad_alloc();
    }
    // object does not exist yet?
    //if (logger)
    //{
    //    logger -> log(clib::LogLevel::DEBUG, "Allocating " + std::to_string(size) + " bytes at " + clib::pointer_to_string(ptr));
    //}
    total_allocated_memory += size;
    return ptr;
};

void *operator new[](std::size_t size)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        throw std::bad_alloc();
    }
    // logger.log(clib::LogLevel::DEBUG, "Allocating array of" + std::to_string(size) + " bytes at " + clib::pointer_to_string(ptr));
    add_allocation(ptr, size);
    total_allocated_memory += size;
    return ptr;
}

void operator delete(void *memory, size_t size) noexcept
{
    // logger.log(clib::LogLevel::DEBUG, "Freeing " + clib::pointer_to_string(memory) + " (" + std::to_string(size) + " bytes)");
    free(memory);
    total_allocated_memory -= size;
};

void operator delete[](void *memory) noexcept
{
    size_t size = get_size(memory);
    operator delete(memory, size);
    remove_allocation(memory);
}