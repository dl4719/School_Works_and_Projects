#ifndef SENECA_LOGGER_H
#define SENECA_LOGGER_H

#include "event.h"

namespace seneca
{
	class Logger
	{
		Event* m_events;
		
		size_t m_size;
		size_t m_capacity;

		void resize(size_t newCapacity);

	public:
		Logger();
		~Logger();
		Logger(const Logger& src);
		Logger& operator =(const Logger& src);
		Logger(Logger&& src) noexcept;
		Logger& operator =(Logger&& src) noexcept;

		void addEvent(const Event& src);

		friend std::ostream& operator <<(std::ostream& os, const Logger& src);
	};
}

#endif //SENECA_LOGGER_H