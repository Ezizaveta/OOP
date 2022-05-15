#pragma once
#include <iostream>
#include <fstream>
#include "Parser.h"

class FrequencyDictionary
{
public:
	virtual ~FrequencyDictionary() = default;

	virtual void addWord(const std::string& word) abstract;
	virtual bool ResetEnumerator() abstract;
	virtual std::pair<std::string, size_t> getNext() abstract;
	virtual bool IteratorIsEnd() abstract;
};