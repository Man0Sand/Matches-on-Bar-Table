#ifndef USER_IO_H
#define USER_IO_H

#include <iostream>
#include <string>

namespace user_IO
{
	inline void ignore_line(std::istream& in)
	{
		char ch;
		while (in.get(ch) && ch != '\n')
			;
	}

	inline char get_user_input()
	{
		char user_input;
		user_input = std::cin.get();
		if (user_input != '\n')
		{
			ignore_line(std::cin);
		}
		return user_input;
	}

	inline void get_user_input(std::string* p_user_input)
	{
		std::cin >> *p_user_input;
		if (*p_user_input != "\n")
		{
			user_IO::ignore_line(std::cin);
		}
	}
	
	inline void prompt_for_enter()
	{
		get_user_input();
	}
}

#endif // USER_IO_H