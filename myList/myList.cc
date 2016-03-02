// myList.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
//#include "myList.h"
#include "doubleLinkedList.h"
#include "singleLinkedList.h"

template<typename T>
singleLinkedList<T> rev(singleLinkedList<T> l)
{
	l.reverse();
	return l;
}

template<typename T>
doubleLinkedList<T> rev(doubleLinkedList<T> l)
{
	l.reverse();
	return l;
}

int _tmain(int argc, _TCHAR* argv[])
{
	singleLinkedList <int> l;
	if (l.is_empty()) for (int i = 1; i<5; i++) l.add_elem(i);
	//singleLinkedList <int> ll = rev(l);
	singleLinkedList <int> ll;
	if (ll.is_empty()) for (int i = 4; i<4; i++) ll.add_elem(i);
	l.show();
	std::cout << "\n";
	l.reverse();
	l.show();
	std::cout << "\n";
	l.del_elem();
	l.show();
	std::cout << "\n" << l.list_size() << "\n";
	l = ll;
	singleLinkedList <int>::iterator pr;
	for (pr = l.begin(); pr != l.end(); pr++) std::cout << *pr << "\n";
	l.show();
	std::cout << "\n";
	//l.~singleLinkedList();

	doubleLinkedList <int> l1;
	if (l1.is_empty()) for (int i = 1; i<5; i++) l1.add_elem(i);
	//doubleLinkedList <int> l2 = rev(l1);
	doubleLinkedList <int> l2;
	if (l2.is_empty()) for (int i = 4; i<4; i++) l2.add_elem(i);
	l1.show();
	std::cout << "\n";
	l1.reverse();
	l1.show();
	std::cout << "\n";
	l1.del_elem();
	l1.show();
	std::cout << "\n" << l1.list_size() << "\n";
	l1 = l2;
	auto pr1 = l1.begin();
	for (pr1; pr1 != l1.end(); pr1++) std::cout << *pr1 << "\n";
	l1.show();
	std::cout << "\n";
	//l1.~doubleLinkedList();
	int n;
	std::cin >> n;
	return 0;
}

