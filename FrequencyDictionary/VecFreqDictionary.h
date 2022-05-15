#pragma once
#include <algorithm>
#include <iterator>
#include <vector>
#include <ctime>
#include "FrequencyDictionary.h"
#include "Parser.h"

class VecFreqDictionary : public FrequencyDictionary
{
private:
	std::vector<std::pair<std::string, size_t>> Dictionary;
	std::vector<std::pair<std::string, size_t>>::iterator DictIterator;
public:
	VecFreqDictionary() = default;
	~VecFreqDictionary() = default;

	void addWord(const std::string& word) override;
	bool ResetEnumerator() override;
	std::pair<std::string, size_t> getNext() override;
	bool IteratorIsEnd() override { return DictIterator == Dictionary.end(); };

	std::vector<std::pair<std::string, size_t>>::iterator findWord(const std::string& word);
};