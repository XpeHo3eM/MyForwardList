#include <iostream>
#include "MyForwardList.h"
#include <forward_list>


int main() {
	MyForwardList<int> list;

	for (int i = 0; i < 5; ++i) {
		list.insert(i);
	}

	auto list2 = list;
	list2.insert(42);

	MyForwardList<int> list3(list);
	list3 = list2;
}