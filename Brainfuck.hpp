#pragma once
#include <iostream>
#include <fstream>
#include <vector>


enum InstType 
{
	chev_l = '<',
	chev_r = '>',
	bracket_start = '[',
	bracket_end = ']',
	point = '.',
	none = '\0',
	plus = '+',
	minus = '-',
	sharp = '#',
	comma = ','
};


class Brainfuck
{
public:
	Brainfuck();
	~Brainfuck();
	enum InstType Interpret(char ch);
	bool ExecFromString(const std::string &str);
	bool ExecFromFile(const std::string &filename);


private:
	std::vector<char> m_memory;
	unsigned int m_mem_size;
	unsigned int m_cmptr;
};

