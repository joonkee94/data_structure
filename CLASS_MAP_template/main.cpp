#include "pch.h"
#include "Cmap.h"
#include <iostream>

int main()
{
    std::cout << "insert 부분 확인"; 

	MAP <int, int> test;

	test.insert(makepair(2, 1));

	test.insert(makepair(3, 1));

	test.insert(makepair(1, 1));

	test.insert(makepair(4, 1));

	test.find(4);


	return 0;
}