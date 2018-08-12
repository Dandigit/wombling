#include <iostream>
#include "../wom/womcolor.h"
#include "../wom/womtime.h"
#include "../wom/womio.h"


int main()
{
	wom::timer t;
	wom::setColor("red");
	std::cout << "Alert! Alert!\n";
	wom::setColor("green");
	std::cout << "Oh - it's OK now.\n";
	wom::resetColor();
	std::cout << "Back to normal.\nExecuted in " << t.elapsed() << " milliseconds.\n";

	wom::time currentTime;
	std::cout << "The current time is " << currentTime << "\n";

	t.restart();
	wom::sleep(5327);
	std::cout << "Waited for " << t.elapsed() << " milliseconds.\n";

	wom::pause();
}