/* The Wombling General Purpose Library
 * Copyright (c) 2018 Daniel Boulton
 *
 * https://github.com/Dandigit/wombling
 */

/* womsys.h
 * System call abstractions; execute
 * a process and get its output and
 * return code.
 */

#ifndef WOMSYS_H
#define WOMSYS_H

#include <cstdio>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <array>

namespace wom
{
	inline std::shared_ptr<FILE> openProcess(std::string command, std::string option)
	{
		#ifdef _WIN32
		std::shared_ptr<FILE> pipe{ _popen(command.c_str(), option.c_str()) };
		#else
		std::shared_ptr<FILE> pipe{ popen(command.c_str(), option.c_str()) };
		#endif

		return pipe;
	}

	inline int closeProcess(std::shared_ptr<FILE> pipe)
	{
		#ifdef _WIN32
		return _pclose(pipe.get());
		#else
		return pclose(pipe.get());
		#endif
	}

	inline std::string exec(std::string command, bool printOutput = false)
	{
		std::array<char, 128> buffer;
		std::string output{ "" };
		int exitCode{ 0 };

		std::shared_ptr<FILE> pipe{ openProcess(command, "r") };
		if (!pipe) throw std::runtime_error("popen() failed in wom::exec!");

		try
		{
			while (!feof(pipe.get())) {
				if (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
				{
					output += buffer.data();
					if (printOutput)
					{
						std::cout << buffer.data();
						std::cout.flush();
					}
				}
			}
		}
		catch (...) {
			exitCode = closeProcess(pipe);
			throw;
		}

		exitCode = closeProcess(pipe);
		return output;
	}
}

#endif
