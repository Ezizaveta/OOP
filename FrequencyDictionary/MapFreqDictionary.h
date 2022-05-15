#pragma once
#include <algorithm>
#include <iterator>
#include <map>
#include <ctime>
#include "FrequencyDictionary.h"
#include "Parser.h"

class MapFreqDictionary : public FrequencyDictionary
{
private:
	std::map<std::string, size_t> Dictionary;
	std::map<std::string, size_t>::iterator DictIterator;
public:
	MapFreqDictionary() = default;
	~MapFreqDictionary() = default;

	void addWord(const std::string& word) override;
	bool ResetEnumerator() override;
	std::pair<std::string, size_t> getNext() override;
	bool IteratorIsEnd() override { return DictIterator == Dictionary.end(); };
};