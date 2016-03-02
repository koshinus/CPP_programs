#include <iostream>
#include <fstream>
#include <stack>
#include <cstring>
using namespace std;

char brackets(char bracket)
{
	switch(bracket)
	{
		case '(' : return ')';
		case '[' : return ']';
		case '{' : return '}';
		case '<' : return '>';
	}
}

int correctBrackets(char *file)
{
	ifstream fromFile;
	fromFile.open(file);
	if (!fromFile.is_open()) return 2;
	
	stack <char> bracket;
	stack <int> positions;
	
	int i=0;
	
	while(true)
	{
	char symbol = fromFile.get();
	i++;
		if (symbol==EOF) //Условия выхода из цикла
			{
				if ( bracket.empty() ) //Проверка стека на пустоту
					{
						fromFile.close();
						return 0;
					}
				else 
					{
						fromFile.close();
						return positions.top();
					}
			}
			else if( symbol=='(' || symbol=='[' || symbol=='{' || symbol=='<' )
				{
					bracket.push( brackets(symbol) ); //Случай когда мы встречаем открывающую скобку
					positions.push(i);
					continue;
				}
				else if(symbol==')' || symbol==']' || symbol=='}' || symbol=='>') //Случай когда встречаем закрывающую скобку
				{
					if( symbol==bracket.top() ) 
					{
						bracket.pop();
						positions.pop();
						continue;
					}
					else 
						{
							fromFile.close();
							return positions.top();
						}
				}
	}
}

void resFile(int res)
{
	ofstream toFile;
	toFile.open("resultFile.txt");
	
	switch(res)
	{
		case 0: 
		{
			toFile << "All right, no mistakes.";
			break;
		}
		case 2: 
		{
			toFile << "Error: impossible to find or open your input file!";
			break;
		}
		default : 
		{
			toFile << "Error in " << res << " position: closing bracket is not right or closing brackets are more than opening!";
			break;
		}
	}
	
	cout << "Result in \"resultFile.txt\".";
}

int main()
{
	char file[260];
	cout << "Enter the name of file: ";
	cin.getline(file,260);
	resFile( correctBrackets(file) );

return 0;
}