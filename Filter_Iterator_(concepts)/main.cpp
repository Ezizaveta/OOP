#include "FilterIteratorConcepts.h"
#include <vector>
#include <iostream>
#include <functional>

class IsNotConstructibleMyNum final
{
private:
	int num;
public:
	IsNotConstructibleMyNum() = delete;
	IsNotConstructibleMyNum(int t) : num(t) {}
	bool operator()(int x) { return num == x; }
};

int main()
{
	std::function<bool(int)> is_less_3 = [](int x) {return x < 3; };

	std::vector<int> v1{ 1, 2, 3, 4, 2, 7, 1, 123 };
	filter_iterator<IsNotConstructibleMyNum, std::vector<int>::iterator>
		f1(IsNotConstructibleMyNum(7), v1.begin(), v1.end());
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