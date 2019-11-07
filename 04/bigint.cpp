/*
Написать класс для работы с большими целыми числами.
Размер числа ограничен только размером памяти. Нужно поддержать семантику работы с обычным int
Реализовать оператор вывода в поток, сложение, вычитание, унарный минус, все операции сравнения.
std::vector и другие контейнеры использовать нельзя - управляйте памятью сами.
*/

#include <iostream>
#include "bigint.h"

// Some random number
const size_t MINIMAL_BLOCK_LENGHT = 256

BigInt::BigInt() {
    value_vector = new char[MINIMAL_BLOCK_LENGHT];
    buffer_size = MINIMAL_BLOCK_LENGHT;
    value_size = 1;
    sign = true;
    value_vector[0] = '0';
}

BigInt::~BigInt() {
    delete[] value;
}

void BigInt::operator=(int64_t x) {

}

void BigInt::divide(int64_t x) {
    int mod = 0;
    int pointer = 0;

    // get number sign
    if (x < 0) {
        sign = false;
        x *= -1;
    }

    // check overflow
    while (x) {
        mod = x % 10;
        x /= 10;

        value_vector[pointer] = mod;
    }

    value_vector[pointer] = mod;
}
