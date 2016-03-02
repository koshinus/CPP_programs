#pragma once
#include <iostream>

template<typename T>
class doubleLinkedList
{
private:
	struct list_elem
	{
		T el;
		list_elem *next;
		list_elem *prev;
	};
	list_elem *top;
	unsigned long size;
	void next_elem() { top = top->next; };
	void prev_elem() { top = top->prev; };
public:
	doubleLinkedList() { top = NULL; size = 0; };
	bool is_empty() const { return top == NULL && size == 0; };
	unsigned long list_size() { return size; };
	void add_elem(const T &elem)//добавляем элемент
	{
		list_elem *new_el = new list_elem;
		new_el->el = elem;
		new_el->next = top;
		if (is_empty()) new_el->prev = new_el;//случай, когда список изначально пуст
		else
		{
			new_el->prev = top->prev;
			top->prev = new_el;
		}
		top = new_el;
		size++;
	};
	void reverse()//разворот списка, колдуем с указателями
	{
		if (size == 0 || size == 1) return;
		top->prev = top->next;
		top->next = NULL;
		list_elem *start = top;
		list_elem *cur_elem;
		prev_elem();
		while (top->next != NULL)
		{
			cur_elem = top->next;
			top->next = top->prev;
			top->prev = cur_elem;
			prev_elem();
		}
		top->next = top->prev;
		top->prev = start;
	};
	void del_elem()//удаляем элемент
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
			start->prev = top->prev;
			delete top;
			top = start;
			size--;
			break;
		}
		}
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
	~doubleLinkedList()
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
	doubleLinkedList<T> & operator=(doubleLinkedList<T> & l)
	{
		if (this == &l) return *this;
		while (top != NULL) del_elem();
		if (l.is_empty()) return *this;
		list_elem *start_l = l.top;
		l.prev_elem();
		do
		{
			add_elem(l.top->el);
			l.prev_elem();
		} while (l.top != start_l->prev);
		l.top = start_l;
		return *this;
	};
	doubleLinkedList(doubleLinkedList &l)
	{
		top = NULL; size = 0;
		if (l.is_empty()) return;
		list_elem *start_l = l.top;
		do
		{
			l.prev_elem();
			add_elem(l.top->el);
		} while (l.top != start_l);
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
		iterator & operator--()
		{
			ptr = ptr->prev;
			return *this;
		};
		iterator & operator--(int)
		{
			iterator tmp = *this;
			ptr = ptr->prev;
			return tmp;
		};
		bool operator==(iterator &that)
		{
			return this->ptr == that->ptr;
		};
		bool operator!=(iterator &that)
		{
			return !(this == that);
		};
		~iterator() { std::cout << "deleted\n"; };
	};

	iterator begin() { return iterator(top); };
	iterator end() { return iterator(NULL); };
};