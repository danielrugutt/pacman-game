#pragma once

#include <string>

class Console{
public:
	Console(std::string name);
	void writeLine(std::string line);

private:
	std::string m_name;
};

