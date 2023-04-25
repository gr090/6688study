#include<iostream>
#include "skiplist.h"
#include<cassert>


int main() {
	SkipList sl;
	assert(sl.Init(5,2));

	for (int i = 0; i < 15; i++) {
		sl.Insert(i+1);
	}
	sl.Print();

	int level = sl.GetMaxLevel() - 1;
	int findNum = 116;
	LevelNode* node = sl.FindNode(findNum, level);
	if (node) {
		std::cout << "found:" << node->m_real->m_val << ", level: " << level << std::endl;
	}
	else {
		std::cout << "not found:" << findNum << std::endl;
	}

	findNum = 3;
	std::cout << "delete:" << findNum << std::endl;
	sl.Delete(findNum);
	sl.Print();

	findNum = 4;
	std::cout << "delete:" << findNum << std::endl;
	sl.Delete(findNum);
	sl.Print();

	findNum = 3;
	std::cout << "insert:" << findNum << std::endl;
	sl.Insert(findNum);
	sl.Print();

	findNum = 4;
	std::cout << "insert:" << findNum << std::endl;
	sl.Insert(findNum);
	sl.Print();

	findNum = 5;
	std::cout << "insert:" << findNum << std::endl;
	sl.Insert(findNum);
	sl.Print();

	findNum = 6;
	std::cout << "insert:" << findNum << std::endl;
	sl.Insert(findNum);
	sl.Print();

	findNum = 5;
	std::cout << "insert:" << findNum << std::endl;
	sl.Insert(findNum);
	sl.Print();
	return 0;
}
