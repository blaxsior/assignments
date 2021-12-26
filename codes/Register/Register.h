#pragma once
#include "MemMask.h"

using namespace std;

class Register {
protected:
    unsigned char memory{ 0 };
    // 초기 값은 항상 0
public:
    /**
    * 레지스터에 저장된 값을 반환한다.
    * @return 레지스터에 저장된 값
    */
    const unsigned char& get()
    {
        return memory;
    }
    /**
     * 메모리의 내용을 초기화
     * memory &= 0 으로 이루어진다
     */
    void clear()
    {
        // 그냥 0으로 초기화 해도 문제 없다.
        memory &= static_cast<unsigned char>(MemoryMask::CLEAR);
    }
    /**
    * 레지스터의 값을 value로 초기화한다.
    * @param value 초기화할 값
    */
    void set(const unsigned char& value)
    {
        memory = value;
    }
};