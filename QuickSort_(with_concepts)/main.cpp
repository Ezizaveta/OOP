#include <algorithm>
#include <iostream>
#include "QuickSort.h"

int main()
{
	std::vector<double> v1 = { 1.0, 8.0, 5.0, 3.0, 4.0, 2.0 };
	quick_sort::sort(v1.begin(), v1.end());
	for (auto i : v1)
	{
		std::cout << i << " ";
	}
	return 0;
}