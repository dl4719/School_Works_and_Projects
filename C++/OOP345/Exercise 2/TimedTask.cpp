#include "TimedTask.h"

seneca::TimedTask::TimedTask() : m_numRecords(0)
{
}

seneca::TimedTask::TimedTask(const TimedTask& src)
	: m_numRecords(src.m_numRecords), m_startTime(src.m_startTime), m_endTime(src.m_endTime)
{
	for (int i = 0; i < m_numRecords; ++i)
	{
		taskArray[i] = src.taskArray[i];
	}
}

seneca::TimedTask& seneca::TimedTask::operator=(const TimedTask& src)
{
	if (this != &src)
	{
		m_numRecords = src.m_numRecords;
		m_startTime = src.m_startTime;
		m_endTime = src.m_endTime;
		for (int i = 0; i < m_numRecords; ++i)
		{
			taskArray[i] = src.taskArray[i];
		}
	}

	return *this;
}

seneca::TimedTask::~TimedTask()
{
}

void seneca::TimedTask::startClock()
{
	m_startTime = std::chrono::steady_clock::now();
}

void seneca::TimedTask::stopClock()
{
	m_endTime = std::chrono::steady_clock::now();
}

void seneca::TimedTask::addTask(const char* taskName)
{
	if (m_numRecords < m_maxTasks)
	{
		taskArray[m_numRecords].m_taskName = taskName;
		taskArray[m_numRecords].m_units = "nanoseconds";
		taskArray[m_numRecords].m_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(m_endTime - m_startTime);
		m_numRecords++;
	}
}

std::ostream& seneca::operator<<(std::ostream& os, const TimedTask& timedTask)
{
	os << "Execution Times:\n";
	os << "-----------------------------\n";
	for (int i = 0; i < timedTask.m_numRecords; ++i)
	{
		os << std::left << std::setw(21) << timedTask.taskArray[i].m_taskName
			<< std::right << std::setw(13) << timedTask.taskArray[i].m_duration.count()
			<< " " << timedTask.taskArray[i].m_units << "\n";
	}

	os << "-----------------------------\n";
	return os;
}
