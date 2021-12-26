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
    * val�� �ش��ϴ� ���� AC ���������� ���� ���Ѵ�.
    * @param val AC ���������� ���� �������� ��
    */
    void MUL(const int& val)
    {
        ac->set(ac->get() * val);
    }

    /**
    * val�� �ش��ϴ� ���� AC ���������� ���� ���Ѵ�.
    * @param val AC ���������� ���� �������� ��
    */
    void ADD(const int& val)
    {
        ac->set(ac->get() + val);
    }
};