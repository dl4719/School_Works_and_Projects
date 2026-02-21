#ifndef SENECA_TIMEDTASK_H
#define SENECA_TIMEDTASK_H

#include <iostream>
#include <iomanip>
#include <string>
#include <chrono>

namespace seneca
{
	struct Task
	{
		std::string m_taskName;
		std::string m_units;
		std::chrono::steady_clock::duration m_duration;
	};

	class TimedTask
	{
		static const int m_maxTasks = 10;
		int m_numRecords;
		std::chrono::steady_clock::time_point m_startTime;
		std::chrono::steady_clock::time_point m_endTime;
		Task taskArray[m_maxTasks];

	public:
		TimedTask();

		TimedTask(const TimedTask& src);

		TimedTask& operator =(const TimedTask& src);

		~TimedTask();

		void startClock();

		void stopClock();

		void addTask(const char* taskName);

		friend std::ostream& operator <<(std::ostream& os, const TimedTask& timedTask);

	};
}
#endif