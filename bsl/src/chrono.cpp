#include "chrono.h"


namespace bsl {
    Chrono::Chrono()
	{
		start = HRClock::now();
	}

	bool Chrono::isOver() const
	{
		return (HRClock::now() - start > duration);
	}

	void Chrono::reset()
	{
		start = HRClock::now();
	}

	void Chrono::setDuration(milliseconds ms)
	{
		duration = ms;
	}
}
	
