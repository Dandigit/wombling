/* The Wombling General Purpose Library
 * Copyright (c) 2018 Daniel Boulton
 *
 * https://github.com/Dandigit/wombling
 */

/* womcolor.h
 * Functions to manipulate the color and
 * weight of text in stdout.
 */

#ifndef WOMCOLOR_H
#define WOMCOLOR_H

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

namespace wom
{
	inline std::string setColor(std::string color = "reset")
	{
		#ifdef _WIN32
		const HANDLE hConsole{ GetStdHandle(STD_OUTPUT_HANDLE) };;

		if (color == "red")
			SetConsoleTextAttribute(hConsole, 12);
		else if (color == "green")
			SetConsoleTextAttribute(hConsole, 10);
		else if (color == "blue")
			SetConsoleTextAttribute(hConsole, 11);
		else if (color == "yellow")
			SetConsoleTextAttribute(hConsole, 14);
		else if (color == "dark red")
			SetConsoleTextAttribute(hConsole, 4);
		else if (color == "dark green")
			SetConsoleTextAttribute(hConsole, 2);
		else if (color == "dark blue")
			SetConsoleTextAttribute(hConsole, 3);
		else if (color == "bold")
			SetConsoleTextAttribute(hConsole, 15);
		else
			SetConsoleTextAttribute(hConsole, 7);
		#else
		if (color == "red")
			std::cout << "\033[91m";
		else if (color == "green")
			std::cout << "\033[92m";
		else if (color == "blue")
			std::cout << "\033[94m";
		else if (color == "yellow")
			std::cout << "\033[93m";
		else if (color == "dark red")
			std::cout << "\033[31m";
		else if (color == "dark green")
			std::cout << "\033[32m";
		else if (color == "dark blue")
			std::cout << "\033[34m";
		else if (color == "bold")
			std::cout << "\033[1m";
		else
			std::cout << "\033[0m";
		#endif

		return "";
	}

	inline std::string resetColor()
	{
		setColor();
		return "";
	}
}

#endif
