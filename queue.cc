#include<iostream>

template<class T>
struct queue_elem
{
	T el;
	queue_elem *next;
};

template<class T>
class Queue
{
private: 
	typedef queue_elem <T> QE;
	QE *front;
	QE *back;
public:
	Queue()
	{
		front = back = NULL;
	};
	bool is_empty() const
	{
		return front == NULL;
	};
	void enqueue(T &elem)
	{
		QE *new_el = new QE;
		if(is_empty()) 
		{
			front = back = new_el;
			new_el->el = elem;
			new_el->next = new_el;
		}
		else
		{
			new_el->el = elem;
			new_el->next = NULL;
			back->next = new_el;
			back = new_el;
		}
	};
	void dequeue()
	{
		if(is_empty()) std::cout << "Queue is already empty."
		else
		{
			QE *top = front->next;
			delete front;
			front = top;
		}
	};
	T get_front()
	{
		return front->el;
	};
	T get_back()
	{
		return back->el;
	};
	~Queue() 
	{
		QE *cur_el;
		while(front!=NULL) 
		{
			cur_el = front->next;
			delete front;
			front = cur_el;
			std::cout << "\ndeleted";
		}
	};
};