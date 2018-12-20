
#ifndef CHRONO_H
#define CHRONO_H

#include <iostream>
#include <chrono>


namespace bsl {
typedef	std::chrono::high_resolution_clock HRClock;
typedef std::chrono::time_point<std::chrono::high_resolution_clock> TimePoint;

using namespace std::chrono;

class Chrono {

	TimePoint				start;
	milliseconds			duration = 3000ms;

public:
	Chrono();
	bool isOver() const;

	void reset();

	void setDuration(milliseconds ms);

};
}

#endif //CHRONO_H
