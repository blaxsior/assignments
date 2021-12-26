#include <unordered_map>
#include <string>
#include <iostream>

template<typename T>
class TABLE {
protected:
	std::unordered_map<std::string, T> table; // 테이블 구조

public:
	const bool contains(const std::string& value) //포함 여부 반환
	{
		return this->table.contains(value);
	}

	auto getTAB() -> const std::unordered_map<std::string, T>&
	{ // 테이블 반환 . 외부에서는 값 변경이 불가능
		return this->table;
	}

	virtual auto showTAB() -> void
	{
		// 테이블의 엔트리를 보여주는 코드.
		// virtual로 구현하여, 해당 코드를 override 할 수 있게 만들었다.
		std::cout << "--------------------------------" << std::endl;
		if (table.empty())
		{
			std::cout << "there is no entry in this table" << std::endl;
		}
		else {
			for (const auto& arg : table)
			{
				std::cout << "KEY : " << arg.first << "\tVALUE : " << arg.second << std::endl;
			}
		}
		std::cout << "--------------------------------\n" << std::endl;
	}
};