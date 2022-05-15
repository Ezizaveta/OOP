#pragma once
#include <algorithm>
#include <iterator>
#include <ctime>
#include <list>
#include "Parser.h"
#include "FrequencyDictionary.h"

class ListFreqDictionary : public FrequencyDictionary
{
private:
	std::list<std::pair<std::string, size_t>> Dictionary;
	std::list<std::pair<std::string, size_t>>::iterator DictIterator;
public:
	ListFreqDictionary() = default;
	~ListFreqDictionary() = default;

	void addWord(const std::string& word) override;
	bool ResetEnumerator() override;
	std::pair<std::string, size_t> getNext() override;
	bool IteratorIsEnd() override { return DictIterator == Dictionary.end(); };

	std::list<std::pair<std::string, size_t>>::iterator findWord(const std::string& word);
};