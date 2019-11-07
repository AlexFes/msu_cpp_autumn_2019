#pragma once

class BigInt {
public:
    BigInt();
    ~BigInt();

private:
    char* value_vector;
    bool sign;
    size_t buffer_size;
    size_t value_size;
};

char* divide(int x);
