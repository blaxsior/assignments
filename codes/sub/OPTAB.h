#pragma once
#include "TABLE.h"
#include <fstream>
#include "errorHandler.h"
#include "default_name.h"

using namespace std;

class OPTAB : public TABLE<std::string> {
private:
	std::string fileName;
public:
	OPTAB()
		:TABLE()
	{
		fileName = default_optab;
	}
	OPTAB(std::string fileName)
		: fileName(fileName)
	{}
public:
	void operateOpCode() {
		std::fstream fs(fileName, std::ios::in);
		std::string temp;
		std::string operation;
		std::string code;

		if (fs.good()) // 파일이 제대로 열렸다면
		{
			int lineno = 0;
			while (!fs.eof())
			{
				operation.clear();
				code.clear();
				// 문자열 초기화

				lineno += 1; //오류 발생 라인 번호

				std::getline(fs, temp);
				const int length = temp.length();
				for (int i = 0; i < length; i++)
				{
					if (temp[i] == ',')
					{
						operation = temp.substr(0, i); // 0 부터 i 칸
						code = temp.substr(i + 1); // i+1부터 끝까지.
						break;
					}
				}//문자열 구분 코드

				if (operation.empty() || code.empty())
				{
					//둘중 하나라도 텅 비었다면
					printError(errorFormat("Invalid Op Code", "\t", -1, lineno));
				}
				else {
					//성공했다면
					this->table.insert(std::make_pair(operation, code));
				}
			}
		}
		else {
			std::cout << "Can't  find file with name " << this->fileName << std::endl;
			exit(EXIT_FAILURE);
		}
		fs.close();
		return;
	}
	const std::string getOpCode(const std::string& value)
	{
		//this->table.end()
		return this->table[value];
		//없으면 empty를 반환
	}
	void showTAB() override
	{
		cout << "OPTAB" << endl;
		TABLE::showTAB();
	}
};