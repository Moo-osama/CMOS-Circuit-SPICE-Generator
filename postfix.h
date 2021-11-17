#pragma once

#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <stack>       
#include <sstream>

using namespace std;

vector <char> extract_output_labels(string& input_exp)
{
	int found;
	vector <char> output_labels;

	found = input_exp.find("=");
	while (found != string::npos)
	{
		output_labels.push_back(input_exp[found - 1]);
		input_exp.erase(found - 1, 2);
		found = input_exp.find("=");
	}
	return output_labels;
}

bool check_priority(char& operator1, char& operator2)
{
	bool priority_bool = false;

	if ((operator1 == '`' && operator2 == '&') ||
		(operator1 == '`' && operator2 == '|') ||
		(operator1 == '&' && operator2 == '|'))
		priority_bool = true;

	return priority_bool;
}

vector <string> get_postfix_vec(string& input_exp)
{
	vector <string> string_vec;
	vector <string> postfix_vec;
	string current_str, postfix;
	char top_operator;
	std::stack<char> stack;
	stringstream ss(input_exp);

	while (ss.good())
	{
		string substr;
		getline(ss, substr, ';');
		string_vec.push_back(substr);
	}

	for (int i = 0; i < string_vec.size(); i++)
	{
		current_str = string_vec[i];
		for (int i = 0; i < current_str.length(); i++)
		{
			if (current_str[i] == '`' || current_str[i] == '&' || current_str[i] == '|')
			{
				if (!stack.empty())
					top_operator = stack.top();
				while (!stack.empty() && check_priority(top_operator, current_str[i]))
				{
					top_operator = stack.top();
					stack.pop();
					postfix += top_operator;
					if (!stack.empty())
						top_operator = stack.top();
				}
				stack.push(current_str[i]);
			}

			else if (current_str[i] == '(')
				stack.push(current_str[i]);

			else if (current_str[i] == ')' && !stack.empty())
			{
				top_operator = stack.top();
				stack.pop();
				while (!stack.empty() && top_operator != '(')
				{
					postfix += top_operator;
					top_operator = stack.top();
					stack.pop();
				}
			}
			else
				postfix += current_str[i];
		}

		while (!stack.empty())
		{
			top_operator = stack.top();
			stack.pop();
			postfix += top_operator;
		}
		postfix_vec.push_back(postfix);
		postfix = "";
	}
	return postfix_vec;
}
