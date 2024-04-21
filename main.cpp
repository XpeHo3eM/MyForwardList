#include <iostream>
#include <iomanip>
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

void printFormatted(const std::string& str) {
	std::cout << std::setw(50) << std::left << str;
}



int main() {
	printFormatted("Default constructor (list):");
	MyForwardList<int> list;
	for (int i = 0; i < 5; ++i) {
		list.push_back(i);
	}
	print(list);


	printFormatted("After copy constructor (list2):");
	auto list2 = list;
	print(list2);

	printFormatted("After push_back (list2):");
	list2.push_back(42);
	print(list2);

	std::cout << std::setw(50) << "list == list2:" << std::boolalpha << (list == list2) << std::endl;


	printFormatted("Initializer list constructor (list3):");
	MyForwardList<int> list3{ 11, 12, 13 };
	print(list3);


	printFormatted("Copy operator= (list2 = list3):");
	list2 = list3;

	print(list3);

	std::cout << std::setw(50) << "List3 find:" << *list3.find(12) << std::endl;
	printFormatted("List3 after remove:");
	list3.remove(12);
	print(list3);

	printFormatted("List2 after removed from list3:");
	print(list2);

	printFormatted("List3 added elements:");
	list3.push_back(11);
	list3.push_front(11);
	print(list3);

	printFormatted("List3 after remove duplicated elements:");
	list3.remove(11);
	print(list3);

	printFormatted("List4 move constructor from list:");
	MyForwardList<int> list4 = std::move(list);
	print(list4);
	printFormatted("List after move constructor to list4:");
	print(list);

	printFormatted("List move operator= from list4:");
	list = std::move(list4);
	print(list);
	printFormatted("List4 after move operator= to list:");
	print(list4);


	printFormatted("Initializer list constructor double (listD):");
	MyForwardList<double> listD{ 11.2, 12.6, 13.11 };
	print(listD);

}