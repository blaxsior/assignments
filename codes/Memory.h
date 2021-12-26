#pragma once
#include <array>
#include "sub/errorHandler.h"

class Memory {
public:
    static constexpr int MEM_SIZE = 64; // �޸� ������

private:
    int mpt; // �޸� ������
    std::array<unsigned char, Memory::MEM_SIZE> inner;// �������

public:
    Memory()
        : mpt(0)
    {
        clearAll(0);
    }

#pragma region READ
    /**
     * idx�� �ش��ϴ� ��ġ�� �޸��� ���� �о�´�.
     * @param idx   �޸𸮿� �ش��ϴ� ��ġ
     * @return      �ش� �޸� �ּҿ� ����� ��
     */
    const unsigned char& readFrom(const int& idx = 0) // Ư�� �ּ� Ȥ�� 0
    {
        check(idx);
        return inner[idx];
    }

    /**
     * ���� �޸� �����Ͱ� ����Ű�� ��ġ�� �޸��� ���� �о�´�.
     * @return      ���� �޸� �ּҿ� ����� ��
     */
    const unsigned char& readCur() // ���� �޸� �ּ�
    {   
        check(mpt);
        return inner[mpt];
    }

    const unsigned char& readIterCur(const bool& from_0 = false) // ���� �޸� �ּ�
    {
        check(mpt);
        if (from_0)
        {
            clearPtr();
        }
        auto value = inner[mpt];
        incPtr();
        return value;
    }

#pragma endregion

#pragma region WRITE
    /**
     * idx�� �ش��ϴ� ��ġ�� �޸𸮿� value�� ����.
     * @param value �޸𸮿� ���� ��
     * @param idx   �޸𸮿� �ش��ϴ� ��ġ
     */
    void writeAt(const unsigned char& value, const int& idx = 0) // Ư�� �ּ� Ȥ�� 0
    {
        check(idx);
        inner[idx] = value;
    }

    /**
     * ���� �޸� ��ġ�� value�� ����.
     * @param value ���� �޸𸮿� ���� ��
     */
    void writeCur(const unsigned char& value) // ���� �޸� �ּ�
    {
        check(mpt);
        inner[mpt] = value;
    }

    const unsigned char& writeIterCur(const unsigned char& value, const bool& from_0 = false) // ���� �޸� �ּ�
    {
        check(mpt);
        if (from_0)
        {
            clearPtr();
        }
        inner[mpt] = value;
        incPtr();
    }
#pragma endregion

#pragma region CLEAR
    /**
     * idx�� �ش��ϴ� ��ġ�� �޸𸮸� 0���� �ʱ�ȭ�Ѵ�.
     * @param idx ���� �ʱ�ȭ�� ��ġ
     */
    void clearAt(const int& idx) // idx�� �ش��ϴ� ���� clear
    {
        check(idx);
        inner[idx] = 0;
    }

    /**
     * idx�� �ش��ϴ� ��ġ ������ �޸𸮸� ��� 0���� �ʱ�ȭ�Ѵ�.
     * @param idx ���� �ʱ�ȭ�� ���� ��ġ
     */
    void clearFrom(const int& idx)
    {
        check(idx);
        for (int i = idx; i < Memory::MEM_SIZE; i++)
        {
            inner[idx] = 0;
        }
    }
    /**
     * �޸𸮸� defaultValue�� ������ �ϰ������� �ʱ�ȭ�Ѵ�.
     * @param defaultValue �޸𸮸� �ʱ�ȭ �ϴ� ��
     */
    void clearAll(const unsigned char& defaultValue = 0)
    {
        inner.fill(defaultValue);
    }
#pragma endregion

#pragma region POINTER
    /**
     * ���� �޸� �����Ͱ� ����Ű�� �ּҸ� idx�� �����Ѵ�
     * @param idx   ���� �޸𸮰� ����ų �ּ�
     */
    void setPtr(const int& idx)
    {
        mpt = idx;
    }

    /**
     * �޸� �����͸� �ʱ�ȭ�Ѵ�
     */
    void clearPtr()
    {
        setPtr(0);
    }
    /**
    * �޸𸮰� ����Ű�� ���ڸ� ������Ų��.
    * ���ڰ� ������ ���� 0���� ���ư���.
    */
    void incPtr()
    {
        mpt = (mpt + 1) % Memory::MEM_SIZE;
    }

    /**
     * ���� �޸� �����Ͱ� ��ȿ�� �� �������� ���θ� ��ȯ�Ѵ�.
     * @return _check(mpt)
     */
    bool checkPtr()
    {
        return _check(mpt);
    }
#pragma endregion

private:
    /**
     * idx�� ���� �ùٸ� �ε������� �˻��Ѵ�.
     * @param idx �˻��� �ε���
     */
    void check(const int& idx) // �ε����� �˻��Ѵ�.
    {
        if (!_check(idx)) // �߸��� �޸� ����.
        {
            printError("Invalid index");
            exit(EXIT_FAILURE);
        }
    }
    /**
     * ���������� �޸� üũ�� ���Ǵ� �Լ�.
     * �ش� �ε����� ��ȿ���� ���θ� bool ������ ��ȯ�Ѵ�.
     * @param idx üũ�� �޸� ��ġ
     * @return    ���� �Էµ� �ε����� ���� ����
     */
    bool _check(const int& idx)
    {
        return idx >= 0 && idx < Memory::MEM_SIZE;
    }
};