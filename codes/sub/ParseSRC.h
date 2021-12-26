#pragma once
#include <string>
#include "trim.h"

using namespace std;

string getLABEL(string temp)
{
	std::string label = trim(temp.substr(0, 8));
	return label;
}

string getOPERAND(string temp)
{
	std::string operand;
	operand = trim(temp.substr(17));

	return operand;
}

string getOPCODE(string temp)
{
	string opcode = trim(temp.substr(9, 6));//9 인덱스, 6칸
	for (auto& ch : opcode)
	{
		ch = toupper(ch);
	}
	return opcode; // 대문자로 변환하여 보내줌.
}