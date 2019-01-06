/*
**** Kevin Florio CSM20 Fall 2016 Project B
**** Topic B - Extra Credit (TopicBex.cpp)
**** Ignore escape sequences in expression checking
*/

#pragma warning(disable : 4786) // Disable warning 

using namespace std;

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include <string>

#include "LinkedQueue.h"
#include "LinkedStack.h"
#include "Node.h"
#include "PrecondViolatedExcept.h"

bool check(string s);

template<class T>
void displayQueue(LinkedQueue<T>& aQueue);

template<class T>
void displayStack(LinkedStack<T>& aStack);

int main()
{
	int i = 0;
	int count;
	fstream infile;
	string tempstr, filename;

	cout << "Create queue object lq" << endl << endl;
	LinkedQueue<string> lq;

	cout << "Get the file input" << endl << endl;
	cout << "Enter input file name : ";
	
	if (filename.size() == 0) // filename = "TopicB.txt";
	{
		getline(cin, filename);
	}
	else
	{
		cout << filename << endl;
	}
	
	infile.open(filename.c_str(), ios::in); // Open file 
	while (!infile) // If fails loop till correct.
	{
		cout << "The file \"" << filename << "\" cannot be opened." << endl;
		cout << "Enter input file name : ";
		getline(cin, filename);
		infile.open(filename.c_str(), ios::in);
	}

	while (getline(infile, tempstr)) // Fill queue
	{
		lq.enqueue(tempstr);
	}
	infile.close();

	cout << endl;
	cout << "After getting the file input, test other functions********" << endl;
	cout << "Create lq1, a copy of the queue" << endl << endl;

	LinkedQueue<string> lq1{ lq }; // Create lq1, a copy of lq

	cout << "Display the contents of the copy queue lq1 : " << endl;
	displayQueue(lq1);
	
	cout << "\nAttempt to peek the now empty copy queue lq1 : " << endl;
	try
	{
		lq1.peekFront();
	}
	catch (const PrecondViolatedExcept &e) // Catch exception and dispay message
	{
		cout << e.what() << endl;
	}

	cout << "\nAssign lq to lq1 and then display lq1 : " << endl;
	lq1 = lq;
	displayQueue(lq1);
	
	cout << "\n\nPut the first string in lq into a stack of chars, ls1" << endl << endl;

	LinkedStack<char> ls1;
	tempstr = lq.peekFront();

	for (count = 0; count < tempstr.length(); count++)
	{
		ls1.push(tempstr[count]);
	}

	cout << "Create a copy, ls2, of the stack and display the copy : " << endl;
	LinkedStack<char> ls2{ ls1 }; // Create ls2, a copy of ls1
	displayStack(ls2);
	
	cout << endl;

	cout << "\nAssign the first stack, ls1, to the second stack, ls2, and then display the second stack : " << endl;
	ls2 = ls1;
	displayStack(ls2); 
	
	cout << endl;
	cout << "\n\n\nDo the expression checking : \n\n\n";

	while (!lq.isEmpty())
	{
		tempstr = lq.peekFront();
		cout << "The next string is :   " << tempstr;
		if (check(tempstr))
		{
			cout << "   is a correct expression" << endl;
		}
		else
		{
			cout << "   is NOT a correct expression" << endl;
		}
		lq.dequeue();
		cout << endl << endl;
	}

	cout << "Program Over" << endl << endl;
	cout << "Press Enter to end -->";
	cin.get();

	return 0;
}

bool check(string s) // To check if the expression is parenthetically correct.
{					 // Will read each char of the string and compare them against their opposites.
	int i;			 // Also an incorporated check to ignore escape sequences.
	char token;
	LinkedStack <char> st;
	for (i = 0; i < s.length(); i++)
	{
		token = s[i];

		// Extra credit - Ignore escape sequences in expression checking
		if (token == '\\')
		{
			i++;
			switch (s[i])
			{
			case '\'':
			case '\"':
				continue;
				break;
			}
		}

		switch (token)
		{
		case '(':
		case '{':
		case '[':
			st.push(token);
			break;
		}

		switch (token)
		{
		case ')':
		{
			if (st.isEmpty()) return false;
			if (st.peek() == '(') st.pop();
		}
		break;
		case '}':
		{
			if (st.isEmpty()) return false;
			if (st.peek() == '{') st.pop();
		}
		break;
		case ']':
		{
			if (st.isEmpty()) return false;
			if (st.peek() == '[') st.pop();
		}
		break;
		}

		switch (token)
		{
		case '\'':
		case '\"':
			if (st.isEmpty() || st.peek() != token) st.push(token); else st.pop();
			break;
		}
	}

	if (st.isEmpty())
	{
		return true;
	}
	else
	{
		return false;
	}
}

template<class T>
void displayQueue(LinkedQueue<T> &aQueue) // Display a Queue
{
	while (!aQueue.isEmpty())
	{
		cout << aQueue.peekFront() << endl;
		aQueue.dequeue();
	}
}

template<class T>
void displayStack(LinkedStack<T> &aStack) // Display a Stack
{
	while (!aStack.isEmpty())
	{
		cout << aStack.peek() << " ";
		aStack.pop();
	}
}