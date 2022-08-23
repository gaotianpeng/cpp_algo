#include <iostream>
#include <vector>
#include "gtest/gtest.h"
#include "list_tools.h"

using namespace std;
using namespace tools;


TEST(LinkListTest, ReverseList) {
	cout << "reverse list test start\n";
	for (int i = 0; i < 10; i++) {
		ListNode* head = GenRandomList(10, -20, 30);
		PrintList(head);
		FreeList(head);
	}

	cout << "test success\n";
	cout << "reverse list test end\n\n";
}