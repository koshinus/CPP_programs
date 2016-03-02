#include<iostream>

template<class T>
struct stack_elem
{
	T el;
	stack_elem *next;
};

template<class T>
class Stack
{
private: 
	typedef stack_elem <T> SE;
	SE *top;
public:
	Stack()
	{
		top = NULL;
	};
	bool is_empty() const
	{
		return top == NULL;
	};
	void push(T &elem)
	{
		SE *new_el = new SE;
		new_el->el = elem;
		new_el->next = top;
		top = new_el;
	};
	void pop()
	{
		if(is_empty()) std::cout << "Stack is already empty."
		else
		{
			SE *cur_el = top->next;
			delete top;
			top = cur_el;
		}
	};
	T get_top()
	{
		return top->el;
	};
	~Stack() 
	{
		SE *cur_el = top;
		while(top!=NULL) 
		{
			cur_el = top->next;
			delete top;
			top = cur_el;
			std::cout << "\ndeleted";
		}
	};
};