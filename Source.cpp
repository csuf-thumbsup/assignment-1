#include <iostream>
#include <string>

using namespace std;

int main() {
	
	string user_input;
	
	cout << "Enter a postfix expression with a $ at the end: ";
	cin >> user_input;
	//getline(cin, user_input);

	//condense user_input - remove all whitespaces
	//user_input.erase( remove(user_input.begin(), user_input.end(), ' '), user_input.end());

	//string str = user_input;

	//str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());

	std::cout << "Input: " << user_input << "\n";


	return 0;
}