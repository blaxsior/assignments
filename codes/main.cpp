#include <fstream>
#include "CPU.h"
#include "sub/ParseSRC.h"
#include "sub/OPTAB.h"

using namespace std;

int main()
{
    CPU cpu;

    std::string fileName;
    std::cout << "���α׷� �̸��� �Է��ϼ��� : ";

    std::cin >> fileName;
    fileName = trim(fileName);

    fstream f(fileName, std::ios::in);
    if(f.good())
    {
        string temp;
        string opcode;
        string operand;

        OPTAB optab("Optab.txt");
        optab.operateOpCode();

        while(!f.eof())
        {
            getline(f, temp); // ���� �о����
            int int_opcode = stoi(optab.getOpCode(getOPCODE(temp)),nullptr, 2);
            int int_operand = stoi(getOPERAND(temp),nullptr, 16);
            unsigned char data = 0;
            data = (int_opcode<<6) | int_operand;
            cpu.setData(data);
        }
        cpu.endData();
        cpu.showCurMemories(0, 9);

        int from = 0, to = 0;
        while (true)
        {
            try {
                std::cout << "������ ��� ������ �Է��ϼ���!( END : negative value at from / to ) " << std::endl;
                std::cout << "From : ";
                std::cin >> from;
                std::cout << "To : ";
                std::cin >> to;
            } 
            catch (exception e) {
                std::cout << "�߸��� �Է��Դϴ�. �ٽ� �Է��ϼ���!" << std::endl;
                continue;
            }
            if (from < 0 || to < 0)
            {
                std::cout << "���α׷��� �����մϴ�" << std::endl;
                break;
            }
            cpu.act(from, to);
        }
        
    }
    else {
        printError("������ �� �� �����ϴ�");
    }
}