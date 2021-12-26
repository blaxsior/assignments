#pragma once
#include <memory>
#include "../Register/RegisterIR.h"
#include "../Register/RegisterPC.h"
#include "../Register/RegisterAC.h"
#include "../Memory.h"
#include "ALU.h"

class CU{
private:
    std::shared_ptr<RegisterIR> ir;
    std::shared_ptr<RegisterPC> pc;
    std::shared_ptr<RegisterAC> ac;
    std::shared_ptr<Memory> memory;
    std::shared_ptr<ALU> alu;
    
    static enum class CODE // ���ο��� ���� ���α׷��� �����ϱ� ���� �ڵ�
    {
        LDA = 0b00,
        STA = 0b01,
        ADD = 0b10,
        MUL = 0b11
    };
public:
    CU(){}

    CU( std::shared_ptr<RegisterIR> ir,
        std::shared_ptr<RegisterPC> pc,
        std::shared_ptr<RegisterAC> ac,
        std::shared_ptr<Memory> memory,
        std::shared_ptr<ALU> alu    )
    {
        this->ir = ir;
        this->pc = pc;
        this->ac = ac;
        this->memory = memory;
        this->alu = alu;
    }
    /**
    * decode�� ����� ������ opcode �� operand�� �Ǵ��ϰ�, ������ �����Ѵ�.
    */
    void execute(const int& opcode, const int& operand)
    {
        switch (static_cast<CODE>(opcode))
        {
        case CODE::LDA:
            LDA(operand);
            break;
        case CODE::STA:
            STA(operand);
            break;
        case CODE::ADD:
            alu->ADD(operand);
            break;
        case CODE::MUL:
            alu->MUL(operand);
            break;
        default:
            printError("������ �� ���� �ڵ� (CU, execute)");
            exit(EXIT_FAILURE);
        }
    }

private:
    /**
    * operand�� �ش��ϴ� �ּҿ��� �����͸� �о� AC �������Ϳ� ���� �����Ѵ�.
    * @param operand �о�� ���� �޸� �ּ�
    */
    void LDA(const int& operand)
    {
        ac->set(memory->readFrom(operand));
    }
    /**
    * operand�� �ش��ϴ� �ּҿ� AC �������Ϳ� ����� ���� �����Ѵ�.
    * @param operand AC ���������� ������ �� �޸� �ּ�
    */
    void STA(const int& operand)
    {
        memory->writeAt(ac->get(), operand);
    }
};