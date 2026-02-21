#include "ProteinDatabase.h"

std::string seneca::ProteinDatabase::getProteinID(const std::string& header)
{
	size_t  sequenceStart = 0, sequenceEnd = 0, currentIndex = 0;

	// Find the first delimiter
	while (currentIndex < header.size() && header[currentIndex] != '|')
	{
		++currentIndex;
	}
	++currentIndex;
	sequenceStart = currentIndex;

	// Find the second delimiter
	while (currentIndex < header.size() && header[currentIndex] != '|')
	{
		++currentIndex;
	}
	sequenceEnd = currentIndex;

	return header.substr(sequenceStart, sequenceEnd - sequenceStart);
}

seneca::ProteinDatabase::ProteinDatabase() 
	: m_proteinIDArray(nullptr), m_proteinSequence(nullptr), m_proteinCount(0)
{
}

seneca::ProteinDatabase::ProteinDatabase(const std::string& fileName)
	: m_proteinIDArray(nullptr), m_proteinSequence(nullptr), m_proteinCount(0)
{
	std::ifstream file(fileName);

	if (!file)
	{
		return;
	}

	std::string line;

	size_t tempCounter = 0;
	while (std::getline(file, line))
	{
		if (!line.empty() && line[0] == '>')
		{
			++tempCounter;
		}
	}

	if (tempCounter == 0)
	{
		std::cout << "No protein sequence found in the file." << std::endl;
		return;
	}

	m_proteinCount = tempCounter;
	m_proteinIDArray = new std::string[m_proteinCount];
	m_proteinSequence = new std::string[m_proteinCount];

	file.close();
	file.open(fileName);

	if (!file)
	{
		std::cout << "Could not open file properly." << std::endl;
		delete[] m_proteinIDArray;
		delete[] m_proteinSequence;
		m_proteinIDArray = nullptr;
		m_proteinSequence = nullptr;
		return;
	}

	std::string currentSequence;
	size_t indexNum = 0;

	while (std::getline(file, line))
	{
		if (line[0] == '>')
		{
			if (!currentSequence.empty() && indexNum < m_proteinCount)
			{
				m_proteinSequence[indexNum] = currentSequence;
				++indexNum;
				currentSequence.clear();
			}
			if (indexNum < m_proteinCount)
			{
				m_proteinIDArray[indexNum] = getProteinID(line);
			}
		}
		else
		{
			currentSequence += line;
		}

	}

	if (!currentSequence.empty() && indexNum < m_proteinCount)
	{
		m_proteinSequence[indexNum] = currentSequence;
	}
}

seneca::ProteinDatabase::ProteinDatabase(const ProteinDatabase& src)
	: m_proteinIDArray(nullptr), m_proteinSequence(nullptr), m_proteinCount(src.m_proteinCount)
{
	m_proteinIDArray = new std::string[m_proteinCount];
	m_proteinSequence = new std::string[m_proteinCount];

	for (size_t i = 0; i < m_proteinCount; ++i)
	{
		m_proteinIDArray[i] = src.m_proteinIDArray[i];
		m_proteinSequence[i] = src.m_proteinSequence[i];
	}
}

seneca::ProteinDatabase& seneca::ProteinDatabase::operator=(const ProteinDatabase& src)
{
	if (this != &src)
	{
		delete[] m_proteinIDArray;
		delete[] m_proteinSequence;

		m_proteinCount = src.m_proteinCount;

		m_proteinIDArray = new std::string[m_proteinCount];
		m_proteinSequence = new std::string[m_proteinCount];

		for (size_t i = 0; i < m_proteinCount; ++i)
		{
			m_proteinIDArray[i] = src.m_proteinIDArray[i];
			m_proteinSequence[i] = src.m_proteinSequence[i];
		}
	}
	return *this;
}

seneca::ProteinDatabase::ProteinDatabase(ProteinDatabase&& src) noexcept
	: m_proteinIDArray(src.m_proteinIDArray), m_proteinSequence(src.m_proteinSequence), m_proteinCount(src.m_proteinCount)
{
	src.m_proteinIDArray = nullptr;
	src.m_proteinSequence = nullptr;
	src.m_proteinCount = 0;
}

seneca::ProteinDatabase& seneca::ProteinDatabase::operator=(ProteinDatabase&& src) noexcept
{
	if (this != &src)
	{
		delete[] m_proteinIDArray;
		delete[] m_proteinSequence;

		m_proteinIDArray = src.m_proteinIDArray;
		m_proteinSequence = src.m_proteinSequence;
		m_proteinCount = src.m_proteinCount;

		src.m_proteinIDArray = nullptr;
		src.m_proteinSequence = nullptr;
		src.m_proteinCount = 0;
	}
	return *this;
}


seneca::ProteinDatabase::~ProteinDatabase()
{
	delete[] m_proteinIDArray;
	delete[] m_proteinSequence;
}

size_t seneca::ProteinDatabase::size() const
{
	return m_proteinCount;
}

std::string seneca::ProteinDatabase::operator[](size_t index) const
{
	if (index < m_proteinCount)
	{
		return m_proteinSequence[index];
	}
	return "";
}

std::string seneca::ProteinDatabase::getUID(size_t index) const
{
	if (index < m_proteinCount)
	{
		return m_proteinIDArray[index];
	}
	return "None";
}
