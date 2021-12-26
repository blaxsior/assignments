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
    
    static enum class CODE // 내부에서 들어온 프로그램을 구분하기 위한 코드
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
    * decode의 결과로 생성된 opcode 및 operand을 판단하고, 연산을 수행한다.
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
            printError("도달할 수 없는 코드 (CU, execute)");
            exit(EXIT_FAILURE);
        }
    }

private:
    /**
    * operand에 해당하는 주소에서 데이터를 읽어 AC 레지스터에 값을 저장한다.
    * @param operand 읽어올 값의 메모리 주소
    */
    void LDA(const int& operand)
    {
        ac->set(memory->readFrom(operand));
    }
    /**
    * operand에 해당하는 주소에 AC 레지스터에 저장된 값을 저장한다.
    * @param operand AC 레지스터의 내용을 쓸 메모리 주소
    */
    void STA(const int& operand)
    {
        memory->writeAt(ac->get(), operand);
    }
};