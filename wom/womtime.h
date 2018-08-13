/* The Wombling General Purpose Library
 * Copyright (c) 2018 Daniel Boulton
 *
 * https://github.com/Dandigit/wombling
 */

/* womtime.h
 * Classes, functions and operators that
 * expand on and simplify the C standard
 * library's <ctime> header.
 */

#ifndef WOMTIME_H
#define WOMTIME_H

#include <ctime>
#include <iostream>
#include <string>
#include <thread>

namespace wom
{
	class time
	{
		int m_year, m_month, m_day, m_hour, m_minute, m_second;

	public:

		time()
		{
			update();
		}

		time(int dd, int mm, int yy, int h, int m, int s)
		{
			m_year = yy + 1900;
			m_month = mm;
			m_day = dd;
			m_hour = h;
			m_minute = m;
			m_second = s;
		}

		time* update()
		{
			std::time_t utc;
			utc = std::time(nullptr);
			std::tm local;
			localtime_s(&local, &utc);

			m_year = local.tm_year + 1900;
			m_month = local.tm_mon;
			m_day = local.tm_mday;
			m_hour = local.tm_hour;
			m_minute = local.tm_min;
			m_second = local.tm_sec;

			return this;
		}

		std::string str(bool displayAmPm = false) const
		{
			std::string timeString;

			if (!(displayAmPm))
			{
				timeString = std::to_string(m_hour) + ":" +
					(m_minute > 9 ? std::to_string(m_minute) : "0" + std::to_string(m_minute)) + ":" +
					(m_second > 9 ? std::to_string(m_second) : "0" + std::to_string(m_second)) + " " +
					std::to_string(m_day) + "/" +
					(m_month > 9 ? std::to_string(m_month) : "0" + std::to_string(m_month)) + "/" +
					std::to_string(m_year);
			}
			else
			{
				std::string differentiator{ (m_hour < 12 ? "AM" : "PM") };

				timeString = (m_hour <= 12 ? std::to_string(m_hour) : std::to_string(m_hour - 12)) + ":" +
					(m_minute > 9 ? std::to_string(m_minute) : "0" + std::to_string(m_minute)) + ":" +
					(m_second > 9 ? std::to_string(m_second) : "0" + std::to_string(m_second)) + " " + differentiator + " " +
					std::to_string(m_day) + "/" +
					(m_month > 9 ? std::to_string(m_month) : "0" + std::to_string(m_month)) + "/" +
					std::to_string(m_year);
			}

			return timeString;
		}
	};

	class timer
	{
		long double m_msElapsed;
		std::clock_t m_startTime;

	public:

		timer() : m_msElapsed{ 0.0 } 
		{
			restart();
		}

		timer* restart()
		{
			m_startTime = std::clock();
			return this;
		}

		long double elapsed(std::string unit = "ms")
		{
			m_msElapsed = (std::clock() - m_startTime) / (double)(CLOCKS_PER_SEC / 1000);

			if (unit == "ms" || unit == "milliseconds")
				return m_msElapsed;
			if (unit == "s" || unit == "seconds")
				return m_msElapsed * 1000;
			if (unit == "ns" || unit == "nanoseconds")
				return m_msElapsed / 1000000;

			return m_msElapsed;
		}
	};

	void sleep(unsigned int wait)
	{
		timer t;
		while (t.elapsed() < wait) {}
	}
}

std::ostream& operator<<(std::ostream& stream, const wom::time& time)
{
	stream << time.str();
	return stream;
}
#endif