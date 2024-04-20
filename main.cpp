#include <iostream>
#include "MyForwardList.h"



template<class T>
void print(const T& list) {
	if (list.is_empty()) {
		std::cout << "List is empty" << std::endl;
	}

	for (const auto& el : list) {
		std::cout << el << " ";
	}
	std::cout << std::endl;
}



int main() {
	std::cout << "Default constructor (list):\t";
	MyForwardList<int> list;
	for (int i = 0; i < 5; ++i) {
		list.push_back(i);
	}
	print(list);


	std::cout << "After copy constructor (list2):\t";
	auto list2 = list;
	print(list2);

	std::cout << "After push_back (list2):\t";
	list2.push_back(42);
	print(list2);

	std::cout << "list == list2:\t" << std::boolalpha << (list == list2) << std::endl;


	std::cout << "Initializer list constructor (list3):\t";
	MyForwardList<int> list3{ 11, 12, 13 };
	print(list3);


	std::cout << "Copy operator= (list2 = list3):\t";
	list2 = list3;

	print(list3);

	std::cout << "List3 find:\t" << *list3.find(12) << std::endl;
	std::cout << "List3 after remove:\t";
	list3.remove(12);
	print(list3);

	std::cout << "List2 after removed from list3:\t";
	print(list2);

	std::cout << "List3 added elements:\t";
	list3.push_back(11);
	list3.push_front(11);
	print(list3);

	std::cout << "List3 after remove duplicated elements:\t";
	list3.remove(11);
	print(list3);

	std::cout << "List4 move constructor from list:\t";
	MyForwardList<int> list4 = std::move(list);
	print(list4);
	std::cout << "List after move constructor to list4:\t";
	print(list);

	std::cout << "List move operator= from list4:\t";
	list = std::move(list4);
	print(list);
	std::cout << "List4 after move operator= to list:\t";
	print(list4);


	std::cout << "Initializer list constructor double (listD):\t";
	MyForwardList<double> listD{ 11.2, 12.6, 13.11 };
	print(listD);
}