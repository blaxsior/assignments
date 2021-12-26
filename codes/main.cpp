#include <fstream>
#include "CPU.h"
#include "sub/ParseSRC.h"
#include "sub/OPTAB.h"

using namespace std;

int main()
{
    CPU cpu;

    std::string fileName;
    std::cout << "프로그램 이름을 입력하세요 : ";

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
            getline(f, temp); // 라인 읽어오기
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
                std::cout << "수행할 명령 라인을 입력하세요!( END : negative value at from / to ) " << std::endl;
                std::cout << "From : ";
                std::cin >> from;
                std::cout << "To : ";
                std::cin >> to;
            } 
            catch (exception e) {
                std::cout << "잘못된 입력입니다. 다시 입력하세요!" << std::endl;
                continue;
            }
            if (from < 0 || to < 0)
            {
                std::cout << "프로그램을 종료합니다" << std::endl;
                break;
            }
            cpu.act(from, to);
        }
        
    }
    else {
        printError("파일을 열 수 없습니다");
    }
}