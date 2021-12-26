#pragma once
#include <array>
#include "sub/errorHandler.h"

class Memory {
public:
    static constexpr int MEM_SIZE = 64; // 메모리 사이즈

private:
    int mpt; // 메모리 포인터
    std::array<unsigned char, Memory::MEM_SIZE> inner;// 저장공간

public:
    Memory()
        : mpt(0)
    {
        clearAll(0);
    }

#pragma region READ
    /**
     * idx에 해당하는 위치의 메모리의 값을 읽어온다.
     * @param idx   메모리에 해당하는 위치
     * @return      해당 메모리 주소에 저장된 값
     */
    const unsigned char& readFrom(const int& idx = 0) // 특정 주소 혹은 0
    {
        check(idx);
        return inner[idx];
    }

    /**
     * 현재 메모리 포인터가 가리키는 위치의 메모리의 값을 읽어온다.
     * @return      현재 메모리 주소에 저장된 값
     */
    const unsigned char& readCur() // 현재 메모리 주소
    {   
        check(mpt);
        return inner[mpt];
    }

    const unsigned char& readIterCur(const bool& from_0 = false) // 현재 메모리 주소
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
     * idx에 해당하는 위치의 메모리에 value를 쓴다.
     * @param value 메모리에 쓰는 값
     * @param idx   메모리에 해당하는 위치
     */
    void writeAt(const unsigned char& value, const int& idx = 0) // 특정 주소 혹은 0
    {
        check(idx);
        inner[idx] = value;
    }

    /**
     * 현재 메모리 위치에 value를 쓴다.
     * @param value 현재 메모리에 쓰는 값
     */
    void writeCur(const unsigned char& value) // 현재 메모리 주소
    {
        check(mpt);
        inner[mpt] = value;
    }

    const unsigned char& writeIterCur(const unsigned char& value, const bool& from_0 = false) // 현재 메모리 주소
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
     * idx에 해당하는 위치의 메모리를 0으로 초기화한다.
     * @param idx 값을 초기화할 위치
     */
    void clearAt(const int& idx) // idx에 해당하는 곳을 clear
    {
        check(idx);
        inner[idx] = 0;
    }

    /**
     * idx에 해당하는 위치 이후의 메모리를 모두 0으로 초기화한다.
     * @param idx 값을 초기화할 시작 위치
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
     * 메모리를 defaultValue의 값으로 일괄적으로 초기화한다.
     * @param defaultValue 메모리를 초기화 하는 값
     */
    void clearAll(const unsigned char& defaultValue = 0)
    {
        inner.fill(defaultValue);
    }
#pragma endregion

#pragma region POINTER
    /**
     * 현재 메모리 포인터가 가리키는 주소를 idx로 설정한다
     * @param idx   현재 메모리가 가리킬 주소
     */
    void setPtr(const int& idx)
    {
        mpt = idx;
    }

    /**
     * 메모리 포인터를 초기화한다
     */
    void clearPtr()
    {
        setPtr(0);
    }
    /**
    * 메모리가 가리키는 숫자를 증가시킨다.
    * 숫자가 끝까지 가면 0으로 돌아간다.
    */
    void incPtr()
    {
        mpt = (mpt + 1) % Memory::MEM_SIZE;
    }

    /**
     * 현재 메모리 포인터가 유효한 줏 범위인지 여부를 반환한다.
     * @return _check(mpt)
     */
    bool checkPtr()
    {
        return _check(mpt);
    }
#pragma endregion

private:
    /**
     * idx에 대해 올바른 인덱스인지 검사한다.
     * @param idx 검사할 인덱스
     */
    void check(const int& idx) // 인덱스를 검사한다.
    {
        if (!_check(idx)) // 잘못된 메모리 접근.
        {
            printError("Invalid index");
            exit(EXIT_FAILURE);
        }
    }
    /**
     * 내부적으로 메모리 체크에 사용되는 함수.
     * 해당 인덱스가 유효한지 여부를 bool 형으로 반환한다.
     * @param idx 체크할 메모리 위치
     * @return    현재 입력된 인덱스의 진위 여부
     */
    bool _check(const int& idx)
    {
        return idx >= 0 && idx < Memory::MEM_SIZE;
    }
};