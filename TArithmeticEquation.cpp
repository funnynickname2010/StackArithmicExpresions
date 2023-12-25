#include "TArithmeticEquation.h"
#include <string>

void TArithmeticEquation::Parse(string input)
{
	vector<string> vec_input;
	bool is_a_number;

	for (int i = 0; i < input.size(); i++)
	{
		string temp_str = "";
		temp_str.push_back(input[i]);

		vec_input.push_back(temp_str);
	}

	for (int i = 0; i < vec_input.size(); i++)
	{
		is_a_number = 1;

		for (auto& pr : priority)
		{
			if (vec_input[i] == pr.first)
			{
				is_a_number = 0;
			}
		}

		for (auto& service_symbol : { "(", ")", "." })
		{
			if (vec_input[i] == service_symbol)
			{
				is_a_number = 0;
			}
		}
		
		try
		{
			stod(vec_input[i]);
		}
		catch (invalid_argument)
		{
			is_a_number = 0;
		}

		if (is_a_number)
		{
			string temp(vec_input[i]);
			size_t dot_count = 0;

			for (int j = i + 1; j < (vec_input.size() ) ; j++)
			{
				if (vec_input[j] == "." && dot_count < 1)
				{
					dot_count++;
					temp = temp + vec_input[j];
				}

				try
				{
					if (vec_input[j] != ".") {
						stod(vec_input[j]);
						temp = temp + vec_input[j];
					}
					i = j;
				}
				catch (invalid_argument)
				{
					if (vec_input[j] != "")
					{
						break;
					}
				}				
			}

			lexems.push_back(temp);
		}
		else
		{
			lexems.push_back(vec_input[i]);
		}
	}
}

void TArithmeticEquation::ToPostfix()
{
	TStack<string> st;
	string stack_item;

	for (string item : lexems)
	{
		if (item == "(") {
			st.Push(item);
		}
		else if (item == ")") {
			stack_item = st.Pull();
			while (stack_item != "(")
			{
				postfix.push_back(stack_item);
				stack_item = st.Pull();
			}
		}
		else if (item == "+" || item == "*" || item == "/" || item == "-") {
			while (!st.Empty())
			{
				stack_item = st.Pull();
				if ((priority[item] > priority[stack_item]) && (stack_item != "("))
				{
					postfix.push_back(stack_item);
				}
				else
				{
					st.Push(stack_item);
					break;
				}
			}
			st.Push(item);
		}
		/*else if (item == "-") {

			if (!st.Empty())
			{
				stack_item = st.Pull();
				if (stack_item == "(")
				{
 					postfix.push_back("0");
					operands.insert({ "0.0", 0.0 });
				}
				st.Push(stack_item);
			}
			else
			{
				postfix.push_back("0");
				operands.insert({ "0.0", 0.0 });
				st.Push(item);
			}

			while (!st.Empty())
			{
				stack_item = st.Pull();
				if (priority[item] <= priority[stack_item])
				{
					postfix.push_back(stack_item);
				}
				else
				{
					st.Push(stack_item);
				}
			}
			st.Push(item);
		}*/
		else {
			OPERANDS_TYPE temp;
			try
			{
				temp = stod(item);
				operands.insert({ item, temp });
				postfix.push_back(item);
			}
			catch (invalid_argument)
			{
				operands.insert({ item, 0.0 });
				postfix.push_back(item);
			}
		} 
	}
	while (!st.Empty())
	{
		stack_item = st.Pull();
		postfix.push_back(stack_item);
	}
}

TArithmeticEquation::TArithmeticEquation(string infx)
{
	priority = { {"+", 1}, {" - ", 1}, {" * ", 2}, {" / ", 2},};
	Parse(infx);
	ToPostfix();
}

string TArithmeticEquation::GetInfix() const
{
	string result = "";

	for (const auto& str : lexems)
	{
		result += str;
	}

	return result;
}

string TArithmeticEquation::GetPostfix() const
{
	string result = "";

	for (const auto& str : postfix)
	{
		result += str;
	}

	return result;
}

vector<string> TArithmeticEquation::GetOperands() const
{
	vector<string> op;

	for (const auto& item : operands)
	{
		try 
		{
			OPERANDS_TYPE temp = stod(item.first);
		}
		catch (invalid_argument)
		{
			op.push_back(item.first);
		}
	}

	return op;
}

OPERANDS_TYPE TArithmeticEquation::Calculate(const map<string, OPERANDS_TYPE>& values)
{
	for (auto& val : values)
	{
		try
		{
			operands.at(val.first) = val.second;
		}
		catch (out_of_range& e) { }
	}

	TStack<double> st;
	double left_operand, right_operand;

	for (string lexem : postfix)
	{
		if (lexem == "+") {
			right_operand = st.Pull();
			left_operand = st.Pull();
			st.Push(left_operand + right_operand);
		}
		else if (lexem == "-") {
			right_operand = st.Pull();
			left_operand = st.Pull();
			st.Push(left_operand - right_operand);
		}
		else if (lexem == "*") {
			right_operand = st.Pull();
			left_operand = st.Pull();
			st.Push(left_operand * right_operand);
		}
		else if (lexem == "/") {
			right_operand = st.Pull();
			left_operand = st.Pull();
			if (right_operand != 0)
			{
				st.Push(left_operand / right_operand);
			}
			else
			{
				throw exception("OPERANDS_TYPE TArithmeticEquation::Calculate(const map<char, OPERANDS_TYPE>& values) error: division by zero.\n");
			}
		}
		else {
			st.Push(operands[lexem]);
		}
	}
	return st.Pull();
}
