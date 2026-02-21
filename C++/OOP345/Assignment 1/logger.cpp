#include "logger.h"
#include <iostream>

namespace seneca
{
	void Logger::resize(size_t newCapacity)
	{
		Event* newEvents = new Event[newCapacity];

		for (size_t i = 0; i < m_size; ++i)
		{
			newEvents[i] = m_events[i];
		}

		delete[] m_events;
		m_events = new Event[newCapacity];
		m_events = newEvents;
		m_capacity = newCapacity;
	}

	// 0-arg constructor
	Logger::Logger() : m_events(nullptr), m_size(0), m_capacity(0)
	{
	}

	// Destructor
	Logger::~Logger()
	{
		delete[] m_events;
	}

	// Copy constructor
	Logger::Logger(const Logger& src) : m_events(nullptr), m_size(0), m_capacity(0)
	{
		*this = src;
	}

	// Copy assignment
	Logger& Logger::operator=(const Logger& src)
	{
		if (this != &src)
		{
			delete[] m_events;

			m_size = src.m_size;
			m_capacity = src.m_capacity;

			m_events = new Event[m_capacity];
			
			for (size_t i = 0; i < m_size; ++i)
			{
				m_events[i] = src.m_events[i];
			}
		}

		return *this;
	}

	//Move Constructor
	Logger::Logger(Logger&& src) noexcept
		: m_events(src.m_events), m_size(src.m_size), m_capacity(src.m_capacity)
	{
		src.m_events = nullptr;
		src.m_size = 0;
		src.m_capacity = 0;
	}

	//Move assignment
	Logger& Logger::operator=(Logger&& src) noexcept
	{
		if (this != &src)
		{
			delete[] m_events;

			m_events = src.m_events;
			m_size = src.m_size;
			m_capacity = src.m_capacity;

			src.m_events = nullptr;
			src.m_size = 0;
			src.m_capacity = 0;
		}
		return *this;
	}

	void Logger::addEvent(const Event& src)
	{
		if (m_size >= m_capacity)
		{
			resize(m_capacity == 0 ? 1 : m_capacity * 2);
		}
		m_events[m_size++] = src;
	}

	std::ostream& operator<<(std::ostream& os, const Logger& src)
	{
		for (size_t i = 0; i < src.m_size; ++i)
		{
			os << src.m_events[i] << std::endl;
		}

		return os;
	}
}