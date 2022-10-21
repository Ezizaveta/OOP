#include "filter_iterator.h"
#include <vector>
#include <iostream>
#include <functional>

int main()
{
	std::function<bool(int)> is_less_3 = [](int x) {return x < 3; };
	
	std::vector<int> v1{ 1, 2, 3, 4, 2, 7, 1, 123 };
	filter_iterator<std::function<bool(int)>, std::vector<int>::iterator> f1(is_less_3, v1.begin(), v1.end());
	for (size_t i = 0; i < 4; i++)
	{
		try {
			std::cout << *f1 << std::endl;
		}
		catch (std::out_of_range& ex)
		{
			std::cout << ex.what() << std::endl;
			break;
		}
		++f1;
	}
	return 0;
}