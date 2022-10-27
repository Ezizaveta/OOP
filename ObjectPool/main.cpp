#include <iostream>
#include "ObjectPool.h"


int main(int argc, char** argv)
{
	if (argc > 1)
	{
		std::cout << "Format: main\n";
		exit(-1);
	}

	try {
		ObjectPool<int> op(10);
		int* elem = op.alloc(1);
		auto elem1 = op.alloc(1);
		//for (int i = 0; i < 10; ++i)
			//std::cout << *(arr.get() + i) << std::endl;
		std::cout << *elem << " " << *elem1 << std::endl;

	}
	catch (std::out_of_range)
	{
		std::cout << "pool is already full" << std::endl;
	}

	return 0;
}