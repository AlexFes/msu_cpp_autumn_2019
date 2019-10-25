#include <iostream>

class LinearAllocator
{
public:
    LinearAllocator(size_t maxSize);
    char* alloc(size_t size);
    void reset();

public:
    char* p;
    int count;
};

LinearAllocator::LinearAllocator(size_t maxSize) {
    p = (char*) malloc(maxSize);
    count = maxSize;
    std::cout << "Init successful! Pointer = " << "" << "\n";
}

char* LinearAllocator::alloc(size_t size) {
    std::cout << "Alloc successful! New pointer = " << p + size << "\n";
    return p + size;
}

void LinearAllocator::reset() {
    free(p);
    std::cout << "Memory release successful!\n";
}

int main(int argc, char** argv) {
    LinearAllocator allocator((size_t) argv[1]);
    allocator.alloc((size_t) argv[2]);
    allocator.alloc((size_t) argv[3]);
    allocator.alloc((size_t) argv[4]);
    allocator.reset();
    return 0;
}
