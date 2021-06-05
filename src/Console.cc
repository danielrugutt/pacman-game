#include "Console.hpp"

#include <iostream>

using namespace std;

Console::Console(string name) {
	m_name = name;
}

void Console::writeLine(string line) {
	cout << "[" << m_name << "]: " << line << endl;
}
