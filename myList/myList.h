#pragma once
//#include "doubleLinkedList.h"
//#include "singleLinkedList.h"

template<typename T>
class singleLinkedList
{
protected:
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
	bool is_empty() const { return size == 0; };
	unsigned long list_size() { return size; };
	virtual void show();										//������� ������
	virtual void add_elem(const T &elem);				//��������� �������
	virtual void del_elem();							//������� �������
	virtual void reverse();								//������������� ������
	singleLinkedList & operator=(const singleLinkedList &l);
	singleLinkedList<T>::singleLinkedList(const singleLinkedList<T> &l);
	virtual ~singleLinkedList();
};


template<typename T>
class doubleLinkedList : public singleLinkedList<T>
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
	bool is_empty() const { return size == 0; };
	unsigned long list_size()	{ return size; };
	virtual void show();
	virtual void add_elem(const T &elem);				//��������� �������
	virtual void del_elem();							//������� �������
	virtual void reverse();								//������������� ������
	doubleLinkedList & operator=(const doubleLinkedList &l);
	doubleLinkedList<T>::doubleLinkedList(const doubleLinkedList<T> &l);
	virtual ~doubleLinkedList();
};