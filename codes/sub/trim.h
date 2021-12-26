#pragma once
#include <string>
using namespace std;

const std::string whiteSpace(" \t\f\v\n\r");
//erase�� [start,end)�� ����. ��, end�� ���� �ȵ�.
string rtrim(string
	str, string delimiter = whiteSpace)
{
	size_t found = str.find_last_not_of(delimiter);
	if (found != std::string::npos)
		str.erase(found + 1); // found�� �ε����� �� �� ���� ��ġ
	else
		str.clear();
	return str;
}// ���� �ƴ� ���� ã�Ƽ�, �ش� ���� ������ ����

string ltrim(string str, string delimiter = whiteSpace)
{
	size_t found = str.find_first_not_of(delimiter);
	if (found != std::string::npos)
		str.erase(0, found); //ó������ �߰��� ������.
	else
		str.clear();
	return str;

}

string trim(string str, string delimiter = whiteSpace)
{
	return ltrim(rtrim(str, delimiter), delimiter);
}