#pragma once
#include <map>
#include <vector>
#include <stdexcept>
#include "ExpectedSpendingParser.h"
#include "RealSpendingParser.h"
#include "Date.h"
#include "Spending.h"
#include "CategoryItem.h"
/*auxulary struct for storage of the busget calculating result for another one categories list*/
struct itemInfo
{
	std::vector<CategoryItem> categoriesList;
	double expected_price;
	double real_price;
	double percent;

	bool operator==(const itemInfo& other) const
	{
		return (categoriesList == other.categoriesList);
	}
	bool operator<(const itemInfo& other) const
	{
		return (categoriesList < other.categoriesList);
	}
};

/*main class for budget calculating
1)It stores ExpectedSpendings as a pair of key-item (that is stored in the categories list)
and corresponding categories list
2) vector of realSpendings*/
class Budget
{
private:

	std::map<CategoryItem, Categories> ExpectedSpendings; // <key-category, categories>
	std::vector<Spending> RealSpendings;

	void addExpectedSpendings(Categories& categories);
	void checkOtherSpending(std::vector<itemInfo>& result, double other_spendings);
	std::vector<itemInfo> initResult();
public:
	Budget() = default;
	void expectedSpendingsFiller(ExpectedSpendingParser& parser);
	void realSpendingsFiller(RealSpendingParser& parser);
	std::vector<itemInfo> calculate(const Date& start, const Date& end);
};