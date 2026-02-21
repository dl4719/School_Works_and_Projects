#ifndef SENECA_EVENT_H
#define SENECA_EVENT_H

#include <string>
#include <chrono>
#include <iomanip>

namespace seneca
{
	class Event
	{
		std::string m_eventName;
		std::chrono::nanoseconds m_eventDuration;

	public:
		Event();
		Event(const char* name, const std::chrono::nanoseconds& duration);
		~Event();
		Event(const Event& src);
		Event& operator =(const Event& src);
		friend std::ostream& operator <<(std::ostream& os, const Event& src);
	};
}
#endif //SENECA_EVENT_H
