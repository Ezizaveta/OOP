#pragma once
#include <string>
#include <vector>
/* auxiliary struct for keeping category with its subcategory. Using in other classes/structs */
struct CategoryItem
{
	std::string category;
	std::string subcategory;
	bool operator==(const CategoryItem& other) const
	{
		return  (category == other.category) && (subcategory == other.subcategory);
	}
	bool operator!=(const CategoryItem& other) const
	{
		return (category != other.category) ||
			((category == other.category) && (subcategory != other.subcategory));
	}
	bool operator<(const CategoryItem& other) const
	{
		return  (category < other.category);
	}
};

/* auxiliary struct, keeps categoriesList from one string and expected value
	as sum of these categories
	example:
	"Products+Cafe 100" is categories list included two categories (Products and Cafe)
	and 100 is expected value for such list */
struct Categories
{
	std::vector<CategoryItem> categoriesList;
	double expectedValue;
	bool operator==(const Categories& other) const
	{
		return (categoriesList == other.categoriesList) && (expectedValue == other.expectedValue);
	}
	bool operator<(const Categories& other) const
	{
		return (categoriesList < other.categoriesList);
	}
};