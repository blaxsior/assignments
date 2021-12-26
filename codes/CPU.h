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
     * �ܺηκ��� �����͸� �ϳ� �о� �޸𸮿� �ش� �����͸� ����.
     * @param data  �ܺηκ��� �о���̴� ������
     * @param is_end ���α׷��� �� �о�鿴���� ����
     */
    void setData(const char& data)
    {
        memory->writeCur(data);
        memory->incPtr();
    }
    /**
    * �����͸� ���� �о���� �� ����ϴ� �Լ�.
    */
    void endData()
    {
        memory->clearPtr();
    }

    /**
    * from �ּҺ��� to �ּұ��� ����� �����ϰ�, �޸� �� �������Ϳ� ����� ����� �����ش�.
    * @param
    */
    void act(const int& from, const int& to)
    {
        if (canAccess(from, to))
        {
            cout << "\n[before]" << endl;
            showCurRegisters();
            showCurMemories(0);
            pc->set(from); // PC�� ���� from���� �ʱ�ȭ

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
    * ���� �������Ϳ� ����� ������ �����ش�.
    */
    void showCurRegisters()
    {
        cout << "[Registers]" << endl;
        cout << "[PC] : " << std::dec << static_cast<int>(pc->get()) << endl;
        cout << "[IR] : " << static_cast<int>(ir->get()) << endl;
        cout << "[AC] : " << static_cast<int>(ac->get()) << std::dec << endl;
    }

    /**
    * from���� to���� ����� �޸� �ּҸ� �����ش�.
    * @param from �����ִ� ���� �ּ�
    * @param to   �����ִ� �� �ּ�
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
                if (i % count == 0) // ���� ������ �����ֱ�
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
            printError("�ùٸ��� ���� �޸� �����Դϴ�.(showMemories)");
        }
    }

private:
    /**
    * ���� pc�� ����Ű�� �޸� �ּҿ� ����� ���� ���� �ͼ� ���� ��ȯ�Ѵ�.
    * @return std::pair<int,int> opcode, operand�� ��
    */
    std::pair<int, int> decode()
    {
        ir->set(memory->readFrom(pc->get()));
        //pc�� ����Ű�� �޸� �ּ��� ���� ir�� �����Ѵ�.
        pc->increment(); // pc�� 1 ������Ų��.

        int opcode = (ir->get() & static_cast<int>(MemoryMask::OPCODE)) >> 6;
        int operand = ir->get() & static_cast<int>(MemoryMask::OPERAND);
        //ir�� ����� ���� opcode�� operand�� ������.

        return make_pair(opcode, operand); //opcode�� operand�� ��ȯ�Ѵ�.
    }

    /**
    * ���õ� ������ �޸𸮿� ������ �� �ִ��� ���θ� ��ȯ�Ѵ�.
    */
    const bool&& canAccess(const int& from, const int& to)
    {
        return from >= 0 && from <= to && to < Memory::MEM_SIZE;
    }
};