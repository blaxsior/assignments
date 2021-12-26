#pragma once
#include "Register.h"
#include "../Memory.h"
/**
 * PC ��������
 * �޸� ũ�� �̻��� ���� �Ҵ��� �� ����.
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