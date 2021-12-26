#include <unordered_map>
#include <string>
#include <iostream>

template<typename T>
class TABLE {
protected:
	std::unordered_map<std::string, T> table; // ���̺� ����

public:
	const bool contains(const std::string& value) //���� ���� ��ȯ
	{
		return this->table.contains(value);
	}

	auto getTAB() -> const std::unordered_map<std::string, T>&
	{ // ���̺� ��ȯ . �ܺο����� �� ������ �Ұ���
		return this->table;
	}

	virtual auto showTAB() -> void
	{
		// ���̺��� ��Ʈ���� �����ִ� �ڵ�.
		// virtual�� �����Ͽ�, �ش� �ڵ带 override �� �� �ְ� �������.
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