#include "gtest/gtest.h"
#include "../FrequencyDictionary/FrequencyDictionary.h"
#include "../FrequencyDictionary/ListFreqDictionary.h"
#include "../FrequencyDictionary/MapFreqDictionary.h"
#include "../FrequencyDictionary/Parser.h"
#include "../FrequencyDictionary/VecFreqDictionary.h"
#include "../FrequencyDictionary/Writer.h"
#include <sstream>

TEST(ParserTest, Word)
{
	std::stringstream ss{ "   .word, ;=:word+( word?)[] word{ !}" };
	Parser parser(ss);
	auto p = parser.getWord();
	EXPECT_EQ(p.first[0], "word");
	EXPECT_EQ(p.second, true);
}

TEST(ParserTest, WordWithoutSpaces)
{
	std::stringstream ss{ ".word,;=:word+(word?)[]word{!}" };
	Parser parser(ss);
	auto p = parser.getWord();
	EXPECT_EQ(p.first[0], "word");
	EXPECT_EQ(p.first[1], "word");
	EXPECT_EQ(p.first[2], "word");
	EXPECT_EQ(p.first[3], "word");
	EXPECT_EQ(p.second, true);
}

TEST(ParserTest, DoubleWordWithPunct)
{
	{
		std::stringstream ss{ "word-word" };
		Parser parser(ss);
		auto p = parser.getWord();
		EXPECT_EQ(p.first[0], "word-word");
		EXPECT_EQ(p.second, true);
		
	}
	{
		std::stringstream ss{ "word,word" };
		Parser parser(ss);
		auto p = parser.getWord();
		EXPECT_EQ(p.first[0], "word");
		EXPECT_EQ(p.second, true);
	}
}
TEST(ParserTest, OnlyPunct)
{
	std::stringstream ss{ ",.+?" };
	Parser parser(ss);
	auto p = parser.getWord();
	EXPECT_EQ(p.first.size(), 0);
	EXPECT_EQ(p.second, false);
}
TEST(ParserTest, EmptySstream)
{
	std::stringstream ss{ "     " };
	Parser parser(ss);
	auto p = parser.getWord();
	EXPECT_EQ(p.first.size(), 0);
	EXPECT_EQ(p.second, false);
}
TEST(ParserTest, FilterPunctuationWord)
{
	std::string s = ";=:word+(";
	std::stringstream ss{ "     " };
	Parser parser(ss);
	auto p = parser.filterPunctuatuion(s);
	EXPECT_EQ(p[0], "word");
}
TEST(ParserTest, FilterPunctuation)
{
	std::string s = ",.+?";
	std::stringstream ss{ "     " };
	Parser parser(ss);
	auto p = parser.filterPunctuatuion(s);
	EXPECT_EQ(p.size(), 0);
}
TEST(ParserTest, FilterPunctuationEmpty)
{
	std::string s = "  ";
	std::stringstream ss{ "     " };
	Parser parser(ss);
	auto p = parser.filterPunctuatuion(s);
	EXPECT_EQ(p.size(), 0);
}

TEST(MapMethods, EmptyDictionary)
	{
		MapFreqDictionary dict;
		std::stringstream ss{ "     " };

		Parser parser(ss);
		parser.fillDictionary(&dict);

		std::stringstream oss;
		std::string s;
		writeDictionary(oss, &dict);
		std::getline(oss, s);
		EXPECT_TRUE(s.empty());
	}

TEST(ListMethods, EmptyDictionary)
	{
		ListFreqDictionary dict;
		std::stringstream ss{ "     " };

		Parser parser(ss);
		parser.fillDictionary(&dict);

		std::stringstream oss;
		std::string s;
		writeDictionary(oss, &dict);
		std::getline(oss, s);
		EXPECT_TRUE(s.empty());
	}

TEST(VecMethods, EmptyDictionary)
{
	VecFreqDictionary dict;
	std::stringstream ss{ "     " };

	Parser parser(ss);
	parser.fillDictionary(&dict);

	std::stringstream oss;
	std::string s;
	writeDictionary(oss, &dict);
	std::getline(oss, s);
	EXPECT_TRUE(s.empty());
}

TEST(ComplexDictionary, Map)
{
	MapFreqDictionary mapDict;
	std::stringstream ss{ "     .word, ;=:word+( word?)[] \n word{ !}" };

	Parser parser(ss);
	parser.fillDictionary(&mapDict);

	std::stringstream oss;
	std::string s;
	writeDictionary(oss, &mapDict);
	std::getline(oss, s);
	EXPECT_EQ(s, "word : 4");
	EXPECT_EQ(mapDict.IteratorIsEnd(), true);

	mapDict.addWord("word");
	bool flag = mapDict.ResetEnumerator();
	auto p = mapDict.getNext();
	EXPECT_EQ(p.first, "word");
	EXPECT_EQ(p.second, 5);
	EXPECT_EQ(mapDict.IteratorIsEnd(), true);

	mapDict.addWord("haha");
	flag = mapDict.ResetEnumerator();
	EXPECT_EQ(mapDict.IteratorIsEnd(), false);
	p = mapDict.getNext();
	EXPECT_EQ(p.first, "haha");
	EXPECT_EQ(p.second, 1);

	p = mapDict.getNext();
	p = mapDict.getNext();
	EXPECT_EQ(p.first, "");
	EXPECT_EQ(p.second, 0);

	EXPECT_NO_THROW(mapDict.addWord(""));
}

TEST(ComplexDictionary, Vec)
{
	VecFreqDictionary dict;
	std::stringstream ss{ "   .word, ;=:word+( word?)[] \n word{ !}" };

	Parser parser(ss);
	parser.fillDictionary(&dict);

	std::stringstream oss;
	std::string s;
	writeDictionary(oss, &dict);
	std::getline(oss, s);
	EXPECT_EQ(s, "word : 4");
	EXPECT_EQ(dict.IteratorIsEnd(), true);

	dict.addWord("word");
	bool flag = dict.ResetEnumerator();
	EXPECT_EQ(dict.IteratorIsEnd(), false);
	auto p = dict.getNext();
	EXPECT_EQ(p.first, "word");
	EXPECT_EQ(p.second, 5);
	EXPECT_EQ(dict.IteratorIsEnd(), true);

	dict.addWord("haha");
	flag = dict.ResetEnumerator();
	p = dict.getNext();
	p = dict.getNext();
	EXPECT_EQ(p.first, "haha");
	EXPECT_EQ(p.second, 1);

	p = dict.getNext();
	EXPECT_EQ(p.first, "");
	EXPECT_EQ(p.second, 0);

	EXPECT_NO_THROW(dict.addWord(""));
	auto it = dict.findWord("word");
	EXPECT_EQ(it->first, "word");
	EXPECT_EQ(it->second, 5);
}

TEST(ComplexDictionary, List)
{
	ListFreqDictionary dict;
	std::stringstream ss{ "     .word, ;=:word+( word?)[] \n word{ !}" };

	Parser parser(ss);
	parser.fillDictionary(&dict);

	std::stringstream oss;
	std::string s;
	writeDictionary(oss, &dict);
	std::getline(oss, s);
	EXPECT_EQ(s, "word : 4");
	EXPECT_EQ(dict.IteratorIsEnd(), true);

	dict.addWord("word");
	bool flag = dict.ResetEnumerator();
	EXPECT_EQ(dict.IteratorIsEnd(), false);
	auto p = dict.getNext();
	EXPECT_EQ(p.first, "word");
	EXPECT_EQ(p.second, 5);
	EXPECT_EQ(dict.IteratorIsEnd(), true);

	dict.addWord("haha");
	flag = dict.ResetEnumerator();
	p = dict.getNext();
	p = dict.getNext();
	EXPECT_EQ(p.first, "haha");
	EXPECT_EQ(p.second, 1);
	EXPECT_EQ(dict.IteratorIsEnd(), true);

	p = dict.getNext();
	EXPECT_EQ(p.first, "");
	EXPECT_EQ(p.second, 0);

	EXPECT_NO_THROW(dict.addWord(""));
	auto it = dict.findWord("word");
	EXPECT_EQ(it->first, "word");
	EXPECT_EQ(it->second, 5);
}

TEST(Writer, ListEmpty)
{
	ListFreqDictionary dict;
	std::stringstream ss;
	std::string s;
	writeDictionary(ss, &dict);
	std::getline(ss, s);
	EXPECT_EQ(s, "");
}

TEST(Writer, VecEmpty)
{
	VecFreqDictionary dict;
	std::stringstream ss;
	std::string s;
	writeDictionary(ss, &dict);
	std::getline(ss, s);
	EXPECT_EQ(s, "");
}

TEST(Writer, MapEmpty)
{
	MapFreqDictionary dict;
	std::stringstream ss;
	std::string s;
	writeDictionary(ss, &dict);
	std::getline(ss, s);
	EXPECT_EQ(s, "");
}

TEST(Writer, Nullptr)
{
	std::stringstream ss;
	EXPECT_ANY_THROW(writeDictionary(ss, nullptr));
}

TEST(ParserTest, FillerEmptyStr)
{
	ListFreqDictionary dict;
	std::stringstream ss{ "     " };
	Parser parser(ss);
	parser.fillDictionary(&dict);
	auto flag = dict.ResetEnumerator();
	EXPECT_EQ(flag, false);
}

TEST(ParserTest, Filler)
{
	VecFreqDictionary dict;
	std::stringstream ss{ "     .word, ;=:word+( word?)[] \n word{ !}" };

	Parser parser(ss);
	parser.fillDictionary(&dict);
	auto it = dict.findWord("word");
	EXPECT_EQ(it->first, "word");
	EXPECT_EQ(it->second, 4);
}

TEST(ParserTest, FillerNullptr)
{
	std::stringstream ss;
	EXPECT_ANY_THROW(writeDictionary(ss, nullptr));
}

TEST(MapMethods, ResetEnumeratorThrow)
{
	MapFreqDictionary dict;
	auto flag = dict.ResetEnumerator();
	EXPECT_ANY_THROW(dict.getNext());
	EXPECT_EQ(flag, false);
}

TEST(MapMethods, ResetEnumerator)
{
	MapFreqDictionary dict;
	dict.addWord("word");
	dict.addWord("word");
	bool flag = dict.ResetEnumerator();
	bool iend = dict.IteratorIsEnd();
	EXPECT_EQ(iend, false);
	auto p = dict.getNext();
	iend = dict.IteratorIsEnd();
	EXPECT_EQ(iend, true);
	EXPECT_EQ(p.first, "word");
	EXPECT_EQ(p.second, 2);
	EXPECT_EQ(flag, true);
}

TEST(VecMethods, ResetEnumeratorThrow)
{
	VecFreqDictionary dict;
	auto flag = dict.ResetEnumerator();
	EXPECT_ANY_THROW(dict.getNext());
	EXPECT_EQ(flag, false);
}

TEST(VecMethods, ResetEnumerator)
{
	VecFreqDictionary dict;
	dict.addWord("word");
	dict.addWord("word");
	bool flag = dict.ResetEnumerator();
	bool iend = dict.IteratorIsEnd();
	EXPECT_EQ(iend, false);
	auto p = dict.getNext();
	iend = dict.IteratorIsEnd();
	EXPECT_EQ(iend, true);
	EXPECT_EQ(p.first, "word");
	EXPECT_EQ(p.second, 2);
	EXPECT_EQ(flag, true);
}

TEST(VecMethods, FindWord)
{
	VecFreqDictionary dict;
	dict.addWord("word");
	dict.addWord("word");
	auto it = dict.findWord("word");
	auto it2 = dict.findWord("haha");
	EXPECT_EQ(it->first, "word");
	EXPECT_EQ(it->second, 2);
	EXPECT_EQ(it2, dict.findWord("haha"));
	EXPECT_ANY_THROW(dict.findWord(std::string()));
}

TEST(ListMethods, ResetEnumeratorThrow)
{
	ListFreqDictionary dict;
	auto flag = dict.ResetEnumerator();
	EXPECT_ANY_THROW(dict.getNext());
	EXPECT_EQ(flag, false);
}

TEST(ListMethods, ResetEnumerator)
{
	ListFreqDictionary dict;
	dict.addWord("word");
	dict.addWord("word");
	bool flag = dict.ResetEnumerator();
	bool iend = dict.IteratorIsEnd();
	EXPECT_EQ(iend, false);
	auto p = dict.getNext();
	iend = dict.IteratorIsEnd();
	EXPECT_EQ(iend, true);
	EXPECT_EQ(p.first, "word");
	EXPECT_EQ(p.second, 2);
	EXPECT_EQ(flag, true);
}

TEST(ListMethods, FindWord)
{
	ListFreqDictionary dict;
	dict.addWord("word");
	dict.addWord("word");
	auto it = dict.findWord("word");
	auto it2 = dict.findWord("haha");

	EXPECT_EQ(it->first, "word");
	EXPECT_EQ(it->second, 2);
	EXPECT_EQ(it2, dict.findWord("haha"));
	EXPECT_ANY_THROW(dict.findWord(std::string()));
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}