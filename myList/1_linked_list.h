#pragma once
#include <iostream>

template<typename T>
class singleLinkedList
{
private:
	struct list_elem
	{
		T el;
		list_elem *next;
	};
	list_elem *top;
	unsigned long size;
	void next_elem() { top = top->next; };
public:
	singleLinkedList() { top = NULL; size = 0; };
	bool is_empty() const { return top == NULL && size == 0; };
	unsigned long list_size() { return size; };
	void add_elem(const T &elem)
	{
		list_elem *new_el = new list_elem;
		new_el->el = elem;
		new_el->next = top;
		top = new_el;
		size++;
	};
	void show()						//выводим список
	{
		if (is_empty())
		{
			std::cout << "[]";
			return;
		}
		list_elem *start = top;
		std::cout << "[";
		while (top != NULL)
		{
			std::cout << top->el << ", ";
			next_elem();
		}
		std::cout << "\b\b]";
		top = start;
	};
	void reverse()//разворот списка, колдуем с указателями
	{
		if (size == 0 || size == 1) return;
		list_elem *prev_el = top->next;
		list_elem *next_el = top;
		top->next = NULL;
		top = prev_el;
		while (prev_el != NULL)
		{
			prev_el = top->next;
			top->next = next_el;
			next_el = top;
			top = prev_el;
		}
		top = next_el;
	};
	void del_elem()
	{
		switch (size)
		{
			case 0:
			{
				std::cout << "List is empty, imposable to delete something!";
				break;
			}
			case 1:
			{
				delete top;
				top = NULL;
				size--;
				break;
			}
			default:
			{
				list_elem *start = top->next;
				delete top;
				top = start;
				size--;
				break;
			}
		}
	};
	~singleLinkedList()
	{
		list_elem *cur_el = top;
		while (top != NULL)
		{
			cur_el = top->next;
			delete top;
			top = cur_el;
			//std::cout << "deleted\n";
		}
	};
	singleLinkedList<T> & operator=(singleLinkedList<T> &l)
	{
		if (this == &l) return *this;
		while (top != NULL) del_elem();
		if (l.is_empty()) return *this;
		list_elem *start_l = l.top;
		while (l.top != NULL)
		{
			add_elem(l.top->el);
			l.next_elem();
		}
		reverse();
		l.top = start_l;
		return *this;
	};
	singleLinkedList(singleLinkedList &l)
	{
		top = NULL; size = 0;
		list_elem *start_l = l.top;
		while (l.top != NULL)
		{
			add_elem(l.top->el);
			l.next_elem();
		}
		l.top = start_l;
		reverse();
	};

	class  iterator
	{
	private:
		list_elem *ptr;
	public:
		iterator() : ptr(NULL) {};
		iterator(list_elem *ple) : ptr(ple) {};
		T operator*() { return ptr->el; };
		iterator & operator++() 
		{ 
			ptr = ptr->next; 
			return *this; 
		};
		iterator & operator++(int) 
		{ 
			iterator tmp = *this;
			ptr = ptr->next; 
			return tmp; 
		};
		bool operator==(iterator &that) 
		{
			return this->ptr == that->ptr;
		};
		bool operator!=(iterator &that)
		{
			return this->ptr != that->ptr;
		};
		~iterator() { std::cout << "deleted\n"; };
	};

	iterator begin() { return iterator(top); };
	iterator end() { return iterator(NULL); };
};