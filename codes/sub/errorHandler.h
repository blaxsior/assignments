#pragma once
#include <string>
#include <iostream>
#include <sstream>

void printError(std::string error_message)
{
	std::cout << "[Error] " << error_message << std::endl;
}

std::string errorFormat(std::string error_message, std::string LABEL = "\t", int LOCCTR = -1, int lineNo = -1)
{
	std::stringstream errFormat;
	errFormat << error_message;
	if (LABEL.compare("\t") != 0) // LABEL을 전달받았다면
	{
		errFormat << "\tLABEL : " << LABEL;
	}
	else
	{
		errFormat << "\t\t";
	}

	if (LOCCTR != -1)
	{
		errFormat << "\tLOCCTR : " << LOCCTR;
	}
	else
	{
		errFormat << "\t\t";
	}

	if (lineNo != -1)
	{
		errFormat << "\tLine No : " << lineNo;
	}
	else
	{
		errFormat << "\t\t";
	}

	return errFormat.str();
}