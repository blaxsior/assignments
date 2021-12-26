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

		if (fs.good()) // ������ ����� ���ȴٸ�
		{
			int lineno = 0;
			while (!fs.eof())
			{
				operation.clear();
				code.clear();
				// ���ڿ� �ʱ�ȭ

				lineno += 1; //���� �߻� ���� ��ȣ

				std::getline(fs, temp);
				const int length = temp.length();
				for (int i = 0; i < length; i++)
				{
					if (temp[i] == ',')
					{
						operation = temp.substr(0, i); // 0 ���� i ĭ
						code = temp.substr(i + 1); // i+1���� ������.
						break;
					}
				}//���ڿ� ���� �ڵ�

				if (operation.empty() || code.empty())
				{
					//���� �ϳ��� �� ����ٸ�
					printError(errorFormat("Invalid Op Code", "\t", -1, lineno));
				}
				else {
					//�����ߴٸ�
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
		//������ empty�� ��ȯ
	}
	void showTAB() override
	{
		cout << "OPTAB" << endl;
		TABLE::showTAB();
	}
};