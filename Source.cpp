#include "TStack.h"
#include "TArithmeticEquation.h"
#include <string>
#define OPERANDS_TYPE double


int main()
{
	string str;

	cout << "Input the arithmetic equation: ";
	cin >> str;
	cout << endl;

	TArithmeticEquation equation(str);

	cout << endl << "Infix form: " << equation.GetInfix() << endl;
	cout << endl << "Postfix form: " << equation.GetPostfix() << endl;

	vector<string> operands_in_lexems = equation.GetOperands();
	map<string, OPERANDS_TYPE> operands;

	OPERANDS_TYPE temp_lexem_input;

	for (const auto& lexem : operands_in_lexems)
	{
		cout << endl << "Input operand " << lexem << ":";
		cin >> temp_lexem_input;

		operands.insert({ lexem, temp_lexem_input });
	}
	cout << endl;

	cout << endl << "Result: " << equation.GetInfix() << " = " << equation.Calculate(operands);

	//STACK TESTING CODE STARTS HERE

	/*
	TStack<MY_TYPE> stack;

	//std::cout << stack.Pull() << '\n';

	for (int i = 0; i < 1000000; i++)
	{
		stack.Push(i);
	}

	std::cout << "\n\nNOW PULLING\n\n";

	for (int i = 0; i < 100001; i++)
	{
		MY_TYPE temp_res_pull = -1;

		try
		{
			temp_res_pull = stack.Pull();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << '\n';
		}

		try
		{
			if (i % 1000 == 0) { std::cout << "Stack pulls the following: " << temp_res_pull << '\n'; std::cout << i << '\n'; }
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << '\n';
		}
	}*/
		//STACK TESTING CODE ENDS HERE
}
