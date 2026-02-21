#ifndef SENECA_PROTEINDATABASE_H
#define SENECA_PROTEINDATABASE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace seneca
{
	class ProteinDatabase
	{
		std::string* m_proteinIDArray;
		std::string* m_proteinSequence;
		size_t m_proteinCount;

		std::string getProteinID(const std::string& header);

	public:
		ProteinDatabase();

		ProteinDatabase(const std::string& file);

		ProteinDatabase(const ProteinDatabase& src);

		ProteinDatabase& operator =(const ProteinDatabase& src);

		ProteinDatabase(ProteinDatabase&& src) noexcept;

		ProteinDatabase& operator =(ProteinDatabase&& src) noexcept;

		~ProteinDatabase();

		size_t size() const;

		std::string operator [](size_t index) const;

		std::string getUID(size_t index) const;

	};
}
#endif
