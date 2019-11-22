#pragma once

class LinearAllocator {
public:
    LinearAllocator(size_t maxSize);
    ~LinearAllocator();
    void* alloc(size_t size);
    void reset();
private:
    char* pointer = nullptr;
    size_t size_all = 0;
    size_t size_used = 0;
    size_t align = 8;
};
