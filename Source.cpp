#include "TStack.h"
#define MY_TYPE int

int main()
{
	TStack<MY_TYPE> stack;

	stack.Push(1);

	for (int i = 0; i < 10; i++)
	{
		stack.Push(i);
	}
	
	std::cout << "\n\nNOW PULLING\n\n";
	
	for (int i = 10; i > 0; i--)
	{
		std::cout << i;
		std::cout << stack.Pull() << '\n';
	}
}