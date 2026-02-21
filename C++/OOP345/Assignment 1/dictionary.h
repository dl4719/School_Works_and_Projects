#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>

namespace seneca
{
	enum class PartOfSpeech
	{
        Unknown,
        Noun,
        Pronoun,
        Adjective,
        Adverb,
        Verb,
        Preposition,
        Conjunction,
        Interjection,
	};

    struct Word
    {
        std::string m_word;
        std::string m_definition;
        PartOfSpeech m_pos = PartOfSpeech::Unknown;
    };

    class Dictionary
    {
        Word* m_words = nullptr;
        size_t m_size = 0;
        size_t m_capacity = 0;

        void resize(size_t newCapacity);

    public:
        Dictionary();
        Dictionary(const char* filename);
        ~Dictionary();
        Dictionary(const Dictionary& src);
        Dictionary& operator =(const Dictionary& src);
        Dictionary(Dictionary&& src) noexcept;
        Dictionary& operator =(Dictionary&& src) noexcept;

        void searchWord(const char* word) const;
    };
}

#endif //SENECA_DICTIONARY_H