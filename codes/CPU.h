#pragma once
#include <iostream>
#include "Unit/ALU.h"
#include "Unit/CU.h"
#include "Register/RegisterAC.h"
#include "Register/RegisterIR.h"
#include "Register/RegisterPC.h"
#include "Memory.h"
#include "Register/MemMask.h"
#include <memory>


class CPU {
private:
    std::shared_ptr <ALU> alu;
    CU cu;
    std::shared_ptr<RegisterAC> ac;
    std::shared_ptr<RegisterIR> ir;
    std::shared_ptr<RegisterPC> pc;

    std::shared_ptr<Memory> memory;

public:
    CPU()
    {
        ac = std::make_shared<RegisterAC>();
        ir = std::make_shared<RegisterIR>();
        pc = std::make_shared<RegisterPC>();
        memory = std::make_shared<Memory>();

        alu = std::make_shared<ALU>(ac);

        cu = CU(ir, pc, ac, memory, alu);
    }

    /**
     * 외부로부터 데이터를 하나 읽어 메모리에 해당 데이터를 쓴다.
     * @param data  외부로부터 읽어들이는 데이터
     * @param is_end 프로그램을 다 읽어들였는지 여부
     */
    void setData(const char& data)
    {
        memory->writeCur(data);
        memory->incPtr();
    }
    /**
    * 데이터를 전부 읽어들인 후 사용하는 함수.
    */
    void endData()
    {
        memory->clearPtr();
    }

    /**
    * from 주소부터 to 주소까지 명령을 실행하고, 메모리 및 레지스터에 저장된 결과를 보여준다.
    * @param
    */
    void act(const int& from, const int& to)
    {
        if (canAccess(from, to))
        {
            cout << "\n[before]" << endl;
            showCurRegisters();
            showCurMemories(0);
            pc->set(from); // PC의 값을 from으로 초기화

            for (int i = 0; i <= to-from; i++)
            {
                auto [opcode, operand] = decode();
                cu.execute(opcode, operand);
                cout << "\n[index : " << i << ", execute]" << endl;
                showCurRegisters();
                showCurMemories(0);
            }
        }
        else {
            printError("Cannot Access Memory... (method act)");
            exit(EXIT_FAILURE);
        }
    }

    /**
    * 현재 레지스터에 저장된 값들을 보여준다.
    */
    void showCurRegisters()
    {
        cout << "[Registers]" << endl;
        cout << "[PC] : " << std::dec << static_cast<int>(pc->get()) << endl;
        cout << "[IR] : " << static_cast<int>(ir->get()) << endl;
        cout << "[AC] : " << static_cast<int>(ac->get()) << std::dec << endl;
    }

    /**
    * from에서 to까지 저장된 메모리 주소를 보여준다.
    * @param from 보여주는 시작 주소
    * @param to   보여주는 끝 주소
    */
    void showCurMemories(int from, int to = Memory::MEM_SIZE - 1)
    {
        constexpr int count = 10;
        if (canAccess(from, to))
        {
            cout << "[Memories]" << endl;
            int cond = 0;
            for (int i = from; i <= to; i++)
            {
                if (i % count == 0) // 구간 나눠서 보여주기
                {
                    cout << "\n[" << std::hex << (i < 16 ? "0":"") << i <<std::dec<< "]\t";
                }
                int value = static_cast<int>(memory->readFrom(i));
                cout << std::hex << (value < 16 ? "0" : "") << value << std::dec <<' ';
                if ((i % count) == count - 1 || i == to)
                {
                    cout << endl;
                }
            }
        }
        else
        {
            printError("올바르지 못한 메모리 지정입니다.(showMemories)");
        }
    }

private:
    /**
    * 현재 pc가 가리키는 메모리 주소에 저장된 값을 꺼내 와서 값을 변환한다.
    * @return std::pair<int,int> opcode, operand의 쌍
    */
    std::pair<int, int> decode()
    {
        ir->set(memory->readFrom(pc->get()));
        //pc가 가리키는 메모리 주소의 값을 ir에 저장한다.
        pc->increment(); // pc를 1 증가시킨다.

        int opcode = (ir->get() & static_cast<int>(MemoryMask::OPCODE)) >> 6;
        int operand = ir->get() & static_cast<int>(MemoryMask::OPERAND);
        //ir에 저장된 값을 opcode와 operand로 나눈다.

        return make_pair(opcode, operand); //opcode와 operand을 반환한다.
    }

    /**
    * 제시된 구간의 메모리에 접근할 수 있는지 여부를 반환한다.
    */
    const bool&& canAccess(const int& from, const int& to)
    {
        return from >= 0 && from <= to && to < Memory::MEM_SIZE;
    }
};