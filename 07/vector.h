/*
Написать свой контейнер Vector аналогичный std::vector, аллокатор и итератор произвольного доступа для него.
Из поддерживаемых методов достаточно operator[], push_back, pop_back, empty, size,
clear, begin, end, rbegin, rend, resize, reserve
*/

#pragma once

template <class T>
class Allocator
{
public:
    T* allocate(size_t count) {
        return (T*) malloc(sizeof(T) * count);
    }

    void deallocate(T* ptr, size_t count) {
        free(ptr);
    }

    void construct(T* ptr, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            new (ptr + i) T();
        }
    }

    void construct(T* ptr, T val) {
        new (ptr) T(val);
    }

    void destroy(T* ptr, size_t count) {
        for (size_t i = 0; i < count; ++i) {
            ptr[i].~T();
        }
    }

    size_t max_size() {
        return std::numeric_limits<size_t>::max();
    }
};

template <class T>
class Iterator
{
private:
    bool reverse_;
    T* pointer_;

public:
    Iterator(T* ptr, bool reverse=true) {
        pointer_ = ptr;
        reverse_ = reverse;
    }

    T& operator*() const {
        return *pointer_;
    }

    Iterator& operator+(size_t count) {
        if (reverse_) {
            pointer_ += count;
        } else {
            pointer_ -= count;
        }
        return *this;
    }

    Iterator& operator++() {
        if (reverse_) {
            pointer_++;
        } else {
            pointer_--;
        }

        return *this;
    }

    Iterator& operator-(size_t count) {
        if (reverse_) {
            pointer_ -= count;
        } else {
            pointer_ += count;
        }

        return *this;
    }

    Iterator& operator--() {
        if (reverse_) {
            pointer_--;
        } else {
            pointer_++;
        }

        return *this;
    }

    bool operator==(const Iterator<T>& it) const {
        return pointer_ == it.pointer_;
    }

    bool operator!=(const Iterator<T>& it) const {
        return pointer_ != it.pointer_;
    }
};

template <class T, class Alloc = Allocator<T>>
class Vector {
private:
    Alloc alloc_;
    T* pointer_;
    size_t size_;
    size_t capacity_;

public:
    using iterator = Iterator<T>;

    Vector() {
        size_ = 0;
        capacity_ = 0;
        pointer_ = nullptr;
    }

    Vector(size_t count) {
        pointer_ = alloc_.allocate(count);
        size_ = 0;
        capacity_ = count;
    }

    ~Vector() {
        alloc_.destroy(pointer_, size_);
        alloc_.deallocate(pointer_, capacity_);
    }

    T& operator[](size_t ind) {
        if (ind >= size_ || ind < 0){
            throw std::out_of_range("Index out of range");
        }

        return pointer_[ind];
    }

    void push_back(T&& val) {
        // empty vector
        if (capacity_ == 0) {
            pointer_ = alloc_.allocate(1);
            pointer_[0] = val;
            size_ = 1;
            capacity_ = 1;
        }
        // full vector
        else if (size_ == capacity_) {
            auto new_pointer = alloc_.allocate(capacity_ * 2);

            for (size_t i = 0; i < size_; ++i){
                alloc_.construct(new_pointer + i, pointer_[i]);
            }

            alloc_.destroy(pointer_, size_);
            alloc_.deallocate(pointer_, capacity_);
            pointer_ = new_pointer;
            pointer_[size_++] = val;
            capacity_ *= 2;
        }
        // regular vector
        else {
            pointer_[size_++] = val;
        }
    }

    void pop_back() {
        if (size_ == 0) {
            throw std::runtime_error("Empty vector");
        }

        alloc_.destroy(pointer_ + size_ - 1, 1);
        size_--;
    }

    bool empty() {
        return size_ == 0;
    }

    size_t size() {
        return size_;
    }

    size_t capacity() {
        return capacity_;
    }

    void clear() {
        alloc_.destroy(pointer_, size_);
        size_ = 0;
    }

    iterator begin() {
        return iterator(pointer_);
    }

    iterator end() {
        return iterator(pointer_ + size_);
    }

    iterator rbegin() {
        return iterator(pointer_ + size_ - 1, false);
    }

    iterator rend() {
        return iterator(pointer_ - 1, false);
    }

    void resize(size_t new_size) {
        if (new_size < size_) {
            alloc_.destroy(pointer_ + new_size, size_ - new_size);
            size_ = new_size;
        } else if (new_size > size_) {
            if (new_size > capacity_) {
                auto new_pointer = alloc_.allocate(new_size);

                for (size_t i = 0; i < size_; ++i) {
                    alloc_.construct(new_pointer + i, pointer_[i]);
                }

                alloc_.destroy(pointer_, size_);
                alloc_.deallocate(pointer_, capacity_);
                pointer_ = new_pointer;
                capacity_ = new_size;
            }

            alloc_.construct(pointer_ + size_, new_size - size_);
            size_ = new_size;
        }
    }

    void reserve(size_t new_capacity) {
        if (new_capacity >= size_ && new_capacity > capacity_) {
            T* new_pointer = alloc_.allocate(new_capacity);

            for (size_t i = 0; i < size_; ++i) {
                alloc_.construct(new_pointer + i, pointer_[i]);
            }

            alloc_.destroy(pointer_, size_);
            alloc_.deallocate(pointer_, size_);
            pointer_ = new_pointer;
            capacity_ = new_capacity;
        }
    }
};
