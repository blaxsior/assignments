#pragma once
#include <string>
using namespace std;

const std::string whiteSpace(" \t\f\v\n\r");
//erase는 [start,end)로 삭제. 즉, end는 삭제 안됨.
string rtrim(string
	str, string delimiter = whiteSpace)
{
	size_t found = str.find_last_not_of(delimiter);
	if (found != std::string::npos)
		str.erase(found + 1); // found의 인덱스는 맨 끝 문자 위치
	else
		str.clear();
	return str;
}// 공백 아닌 문자 찾아서, 해당 문자 전까지 삭제

string ltrim(string str, string delimiter = whiteSpace)
{
	size_t found = str.find_first_not_of(delimiter);
	if (found != std::string::npos)
		str.erase(0, found); //처음부터 발견한 곳까지.
	else
		str.clear();
	return str;

}

string trim(string str, string delimiter = whiteSpace)
{
	return ltrim(rtrim(str, delimiter), delimiter);
}