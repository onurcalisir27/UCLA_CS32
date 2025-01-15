#include <iostream>
#include <string>
#include <stack>
#include <cassert>
using namespace std;

int getPrecedence(char c);
string eraseBlanks(string infix);
int InfixtoPostfix(string infix, string& postfix);

int evaluate(string infix, string& postfix, bool& result)
{
	if (InfixtoPostfix(infix, postfix))
		return 1;

	stack<char> stackEvaluate;
	for (size_t i = 0; i < postfix.size(); i++)
	{
		char c = postfix[i];

		if (c == 'T' || c == 'F')
		{
			stackEvaluate.push(c);
		}
		else if (c == '!')
		{
			if (stackEvaluate.empty())
			{
				return 1;
			}
			char op = stackEvaluate.top();
			stackEvaluate.pop();
			if (op == 'T')
				stackEvaluate.push('F');
			if (op == 'F')
				stackEvaluate.push('T');
		}
		else if (c == '&')
		{
			if (stackEvaluate.empty())
			{
				return 1;
			}
			char op1 = stackEvaluate.top();
			stackEvaluate.pop();

			if (stackEvaluate.empty())
			{
				return 1;
			}
			char op2 = stackEvaluate.top();
			stackEvaluate.pop();

			if (op1 == 'F' || op2 == 'F')
				stackEvaluate.push('F');
			else
				stackEvaluate.push('T');
		
		}
		else if (c == '^')
		{
			if (stackEvaluate.empty())
			{
				return 1;
			}
			char op1 = stackEvaluate.top();
			stackEvaluate.pop();

			if (stackEvaluate.empty())
			{
				return 1;
			}

			char op2 = stackEvaluate.top();
			stackEvaluate.pop();

			if (op1 == 'F' && op2 == 'T' || op1 == 'T' && op2 == 'F')
				stackEvaluate.push('T');
			else
				stackEvaluate.push('F');
		}
		
	}
	if (stackEvaluate.size() != 1)
		return 1;

	if (stackEvaluate.top() == 'T')
		result = true;

	if (stackEvaluate.top() == 'F')
		result = false;

	return 0;
}
// Function Implementations
int getPrecedence(char c)
{
	switch (c)
	{
	case '!':
		return 2;
	case '&':
		return 1;
	case '^': 
		return 0;
	default:
		return -1;
	}
}
string eraseBlanks(string infix)
{
	string erased;
	for (size_t i(0); i < infix.size(); i++)
	{
		char c = infix[i];
		if (infix[i] != ' ')
			erased += infix[i];
	}
	return erased;
}
int InfixtoPostfix(string infix, string& postfix)
{
	infix = eraseBlanks(infix);
	int open(0), closed(0);
	for (size_t i = 0; i < infix.size(); i++)
	{
		char c = infix[i];
		if (c == ')') closed++;
		if (c == '(') open++;
	}
	if (closed != open)
		return 1;

	stack<char> parantheses;
	for (int i = 0; i < infix.size(); i++) {
		char c = infix[i];
		switch (c) {
		case '(':
			parantheses.push(c);
			break;
		case ')':
			if (parantheses.empty() || parantheses.top() != '(') return 1;
			parantheses.pop();
			break;
		}
	}
	postfix = "";
	stack<char> operators;
	
	for (size_t i = 0; i < infix.size(); i++)
	{
		char c = infix[i];
		switch (c)
		{
		case 'T':
		case 'F':
			if(i>0)
				if(infix[i-1] == 'T' || infix[i-1] == 'F' || infix[i-1] == ')')
				{
					return 1;
				}
			postfix += c;
			break;
		case '(':
		case '!':
			if(i>0)
				if (infix[i - 1] == 'T' || infix[i - 1] == 'F' || infix[i - 1] == ')')
				{
					return 1;
				}
			operators.push(c);
			break;
		case ')':
			if (i > 0)
				if (infix[i-1] == '&' || infix[i - 1] == '^' || infix[i - 1] == '!' || infix[i - 1] == '(')
				{
					return 1;
				}
			while (operators.top() != '(')
			{
				postfix += operators.top();
				operators.pop();
			}
			operators.pop();
			break;
		case '&':
		case '^':
			if (i > 0)
				if (infix[i - 1] == '&' || infix[i - 1] == '^' || infix[i - 1] == '!' || infix[i - 1] == '(')
				{
					return 1;
				}
			while (!operators.empty() && operators.top() != '(' && getPrecedence(c) <= getPrecedence(operators.top()))
			{
				postfix += operators.top();
				operators.pop();
			}
			operators.push(c);
			break;
		case ' ':
			break;
		default:
			return 1;
		}
	}
	while (!operators.empty())
	{
		postfix += operators.top();
		operators.pop();
	}
	return 0;
}