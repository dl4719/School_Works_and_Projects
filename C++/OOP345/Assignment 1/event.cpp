#include "event.h"
#include "settings.h"

namespace seneca
{
	Event::Event() : m_eventName(""), m_eventDuration(0)
	{
	}
	Event::Event(const char* name, const std::chrono::nanoseconds& duration)
		: m_eventName(name), m_eventDuration(duration)
	{
	}
	Event::~Event()
	{
	}
	Event::Event(const Event& src)
	{
		*this = src;
	}
	Event& Event::operator=(const Event& src)
	{
		if (this != &src)
		{
			m_eventName = src.m_eventName;
			m_eventDuration = src.m_eventDuration;
		}
		return *this;
	}
	std::ostream& operator<<(std::ostream& os, const Event& src)
	{
		static int counter = 0;
		counter++;

		auto duration = src.m_eventDuration.count();
		std::string units = seneca::g_settings.m_time_units;

		if (units == "seconds") {
			duration /= 1000000000;
		}
		else if (units == "milliseconds") {
			duration /= 1000000;
		}
		else if (units == "microseconds") {
			duration /= 1000;
		}

		os << std::setw(2) << std::right << counter << ": "
			<< std::setw(40) << std::right << src.m_eventName << " -> "
			<< std::setw(units == "seconds" ? 2 : units == "milliseconds" ? 5 : units == "microseconds" ? 8 : 11)
			<< duration << " " << units;

		return os;
	}
}
