#include <iostream>
#include <string>
#include <unordered_map>
#include <deque>

using namespace std;


deque<char> split_into_deque(string input)
{
	deque<char> charlist; // deque to work with 

	// iterate through string and push chars to queue
	for (auto i : input)
	{
		if (!isspace(i))
			charlist.push_back(i);
	}

	return charlist;
}

int eval_operation(char operation, int operand1, int operand2)
{
	// operation -= 57; 
	// getting some stupid fucking error when passing in 'operation' or 'charlist[i]'
	// the ascii value gets set to 99 (C), the letter, instead of being, 48 (*), the star symbol
	// gonna try this on my linux desktop to see if its just VStudio being dumb...
	//other than that it should work -___-
	if (operation == '+')
	{
		cout << "\tPerforming Addition!";
		return operand1 + operand2;
	}
	else if (operation == '-')
	{
		cout << "\tPerforming Subtraction!";
		return operand1 - operand2;
	}
	else if (operation == '*')
	{
		cout << "\tPerforming Multiplication!";
		return operand1 * operand2;
	}
	else if (operation == '/')
	{
		cout << "\tPerforming Division!";
		return operand1 / operand2;
	}
	else {
		cout << "Unexpected Error \n";
		return -1;
	}
}

void process_deque(deque<char> charlist, unordered_map<char, char> dict)
{
	for (int i = 0; i < charlist.size(); i++)
	{
		cout << "\ncurrent item: ";
		cout << charlist[i] << endl;
		cout << "i value: " << i << endl;

		// found i to be an operation
		if (charlist[i] == '+' || charlist[i] == '-' || charlist[i] == '/' || charlist[i] == '*')
		{
			//grab the 2 top digits
			int operand1 = (charlist.front() - '0');
			charlist.pop_front();

			// (char_value - '0') is a dirty trick to convert from type<char> -> type<int> implicitly
			int operand2 = (charlist.front() - '0');
			charlist.pop_front();
			
			cout << "\n-----------------\n" << "Performing operation:" << endl;
			cout << "operand1: " << operand1 << endl;
			cout << "operand2: " << operand2 << endl;

			char op = charlist[i];
			cout << "op: ";
			cout << op << endl;


			// we eval the 2 numbers and convert back to type<char> implicitly
			int result = eval_operation(op, operand1, operand2);
			cout << "eval result: ";
			cout << result << endl;

			// remove operation from deque
			charlist.pop_front();
			
			charlist.push_front(result);

			i = 1; //reset i? errors with indexing...

		}
		else // found i to be a char[a-z]
		{
			// check if current element is NOT in our dict
			if (dict.count(charlist[i]) == 0)
			{
				char char_value;
				//Prompt user for the value of "i"
				cout << "Enter the value of " << charlist[i] << ": " << endl;
				cin >> char_value;

				cout << "Before replacing: " << charlist[i] << endl;
				// update/replace i to its "char digit"
				charlist[i] = char_value;

				cout << "After replacing: " << charlist[i] << endl;

				// store into our dict for future use
				dict.emplace(i, char_value);
			}
			else // current element is in our dict
			{
				// update/replace i to its "char digit"
				charlist[i] = dict.find(charlist[i])->second;
			}
		}
			
	}
}


int main() {

	unordered_map<char, char> dict;
	deque<char> charlist;
	string user_input;
	
	// Get user postfix expression
	cout << "Enter a postfix expression with a $ at the end: " << endl;
	getline(cin, user_input);

	user_input.pop_back(); //remove $... we don't need it, lol
	
	charlist = split_into_deque(user_input);
	process_deque(charlist, dict);

	//there will only be one elem in our charlist which is our result

	cout << "Final Value = " << charlist.front();

	return 0;
}
