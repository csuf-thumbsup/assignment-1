/* CPSC 323 - Assignment #1
 * Names: Rogelio Negrete, Ivan Vu, Angelo Salac
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>

using namespace std;

int eval_operation(char operation, int operand1, int operand2)
{
	if (operation == '+')
		return operand1 + operand2;
	else if (operation == '-')
		return operand1 - operand2;
	else if (operation == '*')
		return operand1 * operand2;
	else if (operation == '/')
		return operand1 / operand2;
	else 
	{
		cout << "Unexpected Error \n";
		return -1;
	}
}

void process_expression(string expression)
{
	unordered_map<char, int> dict;
	stack<int> resultlist;

	for (int i = 0; i < expression.length(); i++)
	{
		// check for operations
		if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/')
		{
			int operand1 = resultlist.top(); resultlist.pop();
			int operand2 = resultlist.top(); resultlist.pop();

			//push computed value back onto stack
			resultlist.push(eval_operation(expression[i], operand1, operand2));

		}
		// found to be a char[a-z] ... ignore the $ and spaces
		else if (expression[i] >= 'a' && expression[i] <= 'z')
		{
			// check if current element is NOT in our dict
			if (dict.count(expression[i]) == 0)
			{
				char char_value;
				int int_value;
				// Prompt user for the value of "expression[i]"
				cout << "\nEnter the value of " << expression[i] << ": ";
				cin >> char_value;
				int_value = char_value - '0'; // quick way to convert from char to int

				// push int_value to the stack 
				resultlist.push(int_value);

				// store into our dict for future use
				dict.emplace(expression[i], int_value);
			}
			else // current element is in our dict
			{
				// find our match in the dict
				int int_value = dict.find(expression[i])->second;

				// push int_value to the stack 
				resultlist.push(int_value);
			}
		}

	}

	// there should only be one value left in the stack which is the final value
	cout << "Final Value: " << resultlist.top() << endl;

}

int main() {
	string user_input;
	
	// Get user postfix expression
	cout << "Enter a postfix expression with a $ at the end: " << endl;
	getline(cin, user_input);

	process_expression(user_input);

	return 0;
}