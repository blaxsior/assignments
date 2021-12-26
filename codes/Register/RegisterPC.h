#pragma once
#include "Register.h"
#include "../Memory.h"
/**
 * PC 레지스터
 * 메모리 크기 이상의 값을 할당할 수 없다.
 */
class RegisterPC : public Register {
public:
    void increment()
    {
        memory = (memory + 1) % Memory::MEM_SIZE;
    }

    void add(const unsigned char& index)
    {
        memory = (memory + index) % Memory::MEM_SIZE;
    }
};