#include "dictionary.h"
#include "settings.h"
#include <fstream>
#include <sstream>
#include <iostream>

namespace seneca
{
	void Dictionary::resize(size_t newCapacity)
	{
		Word* newWords = new Word[newCapacity];
		
		for (size_t i = 0; i < m_size; ++i)
		{
			newWords[i] = m_words[i];
		}

		delete[] m_words;
		m_words = newWords;
		m_capacity = newCapacity;
	}

	// 0-arg Constructor
	Dictionary::Dictionary() :m_words(nullptr), m_size(0), m_capacity(0)
	{
	}

	// 1-arg Constructor
	Dictionary::Dictionary(const char* filename) : m_words(nullptr), m_size(0), m_capacity(0)
	{
		std::ifstream file(filename);
		if (!file)
		{
			return;
		}

		std::string line;
		while (std::getline(file, line))
		{
			std::istringstream ss(line);
			std::string word, pos, definition;
			std::getline(ss, word, ',');
			std::getline(ss, pos, ',');
			std::getline(ss, definition);

			PartOfSpeech part = PartOfSpeech::Unknown;
			if (pos == "noun") part = PartOfSpeech::Noun;
			else if (pos == "pronoun") part = PartOfSpeech::Pronoun;
			else if (pos == "adjective") part = PartOfSpeech::Adjective;
			else if (pos == "adverb") part = PartOfSpeech::Adverb;
			else if (pos == "verb") part = PartOfSpeech::Verb;
			else if (pos == "preposition") part = PartOfSpeech::Preposition;
			else if (pos == "conjunction") part = PartOfSpeech::Conjunction;
			else if (pos == "interjection") part = PartOfSpeech::Interjection;

			if (m_size >= m_capacity)
			{
				resize(m_capacity == 0 ? 1 : m_capacity * 2);
			}

			m_words[m_size++] = { word, definition, part };
		}
	}

	// Destructor
	Dictionary::~Dictionary()
	{
		delete[] m_words;
	}

	// Copy constructor
	Dictionary::Dictionary(const Dictionary& src) : m_words(nullptr), m_size(0), m_capacity(0)
	{
		*this = src;
	}

	// Copy assignment
	Dictionary& Dictionary::operator=(const Dictionary& src)
	{
		if (this != &src)
		{
			delete[] m_words;

			m_size = src.m_size;
			m_capacity = src.m_capacity;

			m_words = new Word[m_capacity];

			for (size_t i = 0; i < m_size; i++)
			{
				m_words[i] = src.m_words[i];
			}
		}
		return *this;
	}

	// Move constructor
	Dictionary::Dictionary(Dictionary&& src) noexcept
		: m_words(src.m_words), m_size(src.m_size), m_capacity(src.m_capacity)
	{
		src.m_words = nullptr;
		src.m_size = 0;
		src.m_capacity = 0;
	}

	// Move assignment
	Dictionary& Dictionary::operator=(Dictionary&& src) noexcept
	{
		if (this != &src)
		{
			delete[] m_words;

			m_words = src.m_words;
			m_size = src.m_size;
			m_capacity = src.m_capacity;

			src.m_words = nullptr;
			src.m_size = 0;
			src.m_capacity = 0;
		}
		return *this;
	}

	void Dictionary::searchWord(const char* word) const
	{
		bool found = false;

		for (size_t i = 0; i < m_size; ++i)
		{
			if (m_words[i].m_word == word)
			{
				if (!found)
				{
					std::cout << m_words[i].m_word << " - ";
					if (seneca::g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
						std::cout << "(" << static_cast<int>(m_words[i].m_pos) << ") ";
					}
					std::cout << m_words[i].m_definition << std::endl;
					found = true;
				}
				else {
					std::cout << "       - ";
					if (seneca::g_settings.m_verbose && m_words[i].m_pos != PartOfSpeech::Unknown) {
						std::cout << "(" << static_cast<int>(m_words[i].m_pos) << ") ";
					}
					std::cout << m_words[i].m_definition << std::endl;
				}
				if (!seneca::g_settings.m_show_all) break;
			}
		}
		if (!found)
		{
			std::cout << "Word '" << word << "' was not found in the dictionary." << std::endl;
		}
	}
}