#include "timeMonitor.h"

namespace seneca
{
	void TimeMonitor::startEvent(const char* name)
	{
		m_eventName = name;
		m_startTime = std::chrono::steady_clock::now();
	}

	Event TimeMonitor::stopEvent()
	{
		auto end = std::chrono::steady_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - m_startTime);
		
		return Event(m_eventName.c_str(), duration);
	}
}