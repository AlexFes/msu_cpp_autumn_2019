#include <iostream>
#include <cerrno>
#include <stdlib.h>
#include <cstring>
#include "Allocator.h"

LinearAllocator::LinearAllocator(size_t maxSize) {
    size_all = maxSize % allign ? (maxSize / allign + 1) * allign : maxSize;
    pointer = new char[size_all];
}

LinearAllocator::~LinearAllocator() {
    if (pointer)
        delete[] pointer;
}

void* LinearAllocator::alloc(size_t size) {
    size_t allign = 8;
    size_t tmp_size = size % allign ? size + 1 : size;
    if (tmp_size > size_all - size_used)
        throw std::runtime_error("not enough memory");
    void *tmp_return = pointer + size_used;
    size_used += tmp_size;
    return tmp_return;
}

void LinearAllocator::reset() {
    size_used = 0;
}
