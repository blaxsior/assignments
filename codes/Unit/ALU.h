#pragma once
#include <memory>
#include "Register/RegisterAC.h"

class ALU {
private:
    std::shared_ptr<RegisterAC> ac;
public:
    ALU(){}
    ALU(std::shared_ptr<RegisterAC> ac)
    {
        this->ac = ac;
    }

    /**
    * val에 해당하는 값을 AC 레지스터의 값에 곱한다.
    * @param val AC 레지스터의 값에 곱해지는 값
    */
    void MUL(const int& val)
    {
        ac->set(ac->get() * val);
    }

    /**
    * val에 해당하는 값을 AC 레지스터의 값에 더한다.
    * @param val AC 레지스터의 값에 더해지는 값
    */
    void ADD(const int& val)
    {
        ac->set(ac->get() + val);
    }
};