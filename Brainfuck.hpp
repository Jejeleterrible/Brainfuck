#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>


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


template <typename T>
class Brainfuck
{

public:
	Brainfuck() 
	{
		m_memory.push_back((T)0);
		m_cmptr = 0;
	}

	~Brainfuck()
	{
		m_memory.clear();
	}

	InstType Interpret(T ch)
	{
		switch (ch)
		{
		case chev_r:
			m_cmptr++;
			if (m_memory.size() - 1 < m_cmptr)
			{
				m_memory.push_back(0);
			}
			return chev_r;

		case chev_l:
			m_cmptr--;
			return chev_l;

		case point:
			std::cout << m_memory[m_cmptr];
			return point;

		case bracket_start:
			return bracket_start;

		case bracket_end:
			return bracket_end;

		case plus:
			m_memory[m_cmptr] += 1;
			return plus;

		case minus:
			m_memory[m_cmptr] -= 1;
			return minus;

		case sharp:
			std::cout << "\npointer : \t" << m_cmptr << "\nvalue : \t" << m_memory[m_cmptr] << " ( " << (int)m_memory[m_cmptr] << " )" << std::endl;
			return sharp;

		case comma:
			std::cin >> m_memory[m_cmptr];
		}

		return none;
	}


	bool ExecFromString(const std::string & str)
	{
		int res;

		for (int x = 0; x<str.size(); x++)
		{
			res = Interpret(str[x]);

			if (res == bracket_start)
			{
				if (m_memory[m_cmptr] == 0)
				{
					int nb_brackets = 1;

					while (nb_brackets != 0)
					{
						x++;
						if (str[x] == bracket_start)
						{
							nb_brackets++;
						}
						else if (str[x] == bracket_end)
						{
							nb_brackets--;
						}
					}
				}
			}


			if (res == bracket_end)
			{
				int nb_brackets = 1;

				while (nb_brackets != 0)
				{
					x--;
					if (str[x] == bracket_start)
					{
						nb_brackets--;
					}
					else if (str[x] == bracket_end)
					{
						nb_brackets++;
					}
				}
				x--;
			}
		}

		return true;
	}


	bool ExecFromFile(const std::string &filename)
	{
		std::ifstream file(filename, std::ios::in);

		if (!file)
		{
			std::cerr << "Can't open file \"" << filename << "\" ! " << std::endl;
			return false;
		}

		std::string cur_line;
		std::string code;

		while (getline(file, cur_line))
		{
			code += cur_line;
		}

		file.close();

		ExecFromString(code);

	}


private:
	std::vector<T> m_memory;
	unsigned int m_mem_size;
	unsigned int m_cmptr;
};

