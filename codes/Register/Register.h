#pragma once
#include "MemMask.h"

using namespace std;

class Register {
protected:
    unsigned char memory{ 0 };
    // �ʱ� ���� �׻� 0
public:
    /**
    * �������Ϳ� ����� ���� ��ȯ�Ѵ�.
    * @return �������Ϳ� ����� ��
    */
    const unsigned char& get()
    {
        return memory;
    }
    /**
     * �޸��� ������ �ʱ�ȭ
     * memory &= 0 ���� �̷������
     */
    void clear()
    {
        // �׳� 0���� �ʱ�ȭ �ص� ���� ����.
        memory &= static_cast<unsigned char>(MemoryMask::CLEAR);
    }
    /**
    * ���������� ���� value�� �ʱ�ȭ�Ѵ�.
    * @param value �ʱ�ȭ�� ��
    */
    void set(const unsigned char& value)
    {
        memory = value;
    }
};