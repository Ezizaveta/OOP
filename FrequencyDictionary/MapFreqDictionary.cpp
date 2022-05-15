#include "MapFreqDictionary.h"

void MapFreqDictionary::addWord(const std::string & word)
{
	if (!word.empty())
	{
		Dictionary[word]++;
	}
}

bool MapFreqDictionary::ResetEnumerator()
{
	if (!Dictionary.empty())
	{
		DictIterator = Dictionary.begin();
		return true;
	}

	return false;
}

std::pair<std::string, size_t> MapFreqDictionary::getNext()
{
	if (Dictionary.empty())
	{
		throw std::out_of_range("Dictionary is empty");
	}
		
	if (DictIterator != Dictionary.end())
	{
		std::pair<std::string, size_t> current = *DictIterator;
		DictIterator++;
		return current;
	}
	return std::make_pair(std::string(), 0);
}