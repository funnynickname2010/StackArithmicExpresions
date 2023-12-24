#pragma once
#include <iostream>
#include <vector>
#include <map>

#include "TStack.h"

#define OPERANDS_TYPE double

using namespace std;

class TArithmeticEquation
{
	//vector<string> infix;
	vector<string> postfix;

	vector<string> lexems;

	map<string, int> priority;
	map<string, OPERANDS_TYPE> operands;

	void Parse(string input);
	void ToPostfix();

public:

	TArithmeticEquation(string infx);

	string GetInfix() const;
	string GetPostfix() const;

	vector<string> GetOperands() const;

	OPERANDS_TYPE Calculate(const map<string, OPERANDS_TYPE>& values);
};

