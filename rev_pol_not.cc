#include <iostream>
#include <string>
#include <stack>
using std::cout;

int priorety(const char c)
{
	switch(c)
	{
		case '(' : return 0;
		case ')' : return 0;
		case '+' : return 1;
		case '-' : return 1;
		case '*' : return 2;
		case '/' : return 2;
		case '^' : return 3;
		default  : return 0;
	}
}

int main()
{
	std::string str;
	std::stack <char> operators_stack;
	cout << "Enter string, which you want to transform.\nString mustn't have any spaces: ";
	std::cin >> str;
	for(int i = 0; i < str.size(); i++)
	{
		switch(priorety(str[i]))
		{
			case 0:
				switch(str[i])
				{
					case '(': 
						operators_stack.push(str[i]);
						break;
					case ')': 
						while(operators_stack.top() != '(')
							{
								cout << operators_stack.top();
								operators_stack.pop();
							}
							operators_stack.pop();
						break;
					default  : cout << str[i];
					break;
				}
				break;
			default:
				while( !operators_stack.empty() && (priorety(str[i]) <= priorety(operators_stack.top())) )
				{
					cout << operators_stack.top();
					operators_stack.pop();
				}
				operators_stack.push(str[i]);
				break;
		}
	}
	while( !operators_stack.empty() ) 
	{
		cout << operators_stack.top();
		operators_stack.pop();
	}
return 0;
}