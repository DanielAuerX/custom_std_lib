#pragma once

#include <cstddef>
#include "logging.hpp"


size_t get_memory_usage();
void *operator new(std::size_t size);
void *operator new[](std::size_t size);
void operator delete(void *memory, size_t size) noexcept;
void operator delete[](void *memory) noexcept;
