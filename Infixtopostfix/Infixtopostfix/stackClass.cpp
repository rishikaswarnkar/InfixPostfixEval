#include "stackClass.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <string>
#include <fstream>
#include<stack>
using namespace std;
stackClass::stackClass()
{
	//Receives - Nothing
	//Task - set private pointers to NULL pointer
	//Returns - Nothing
	TopPtr = NULL;
	rear = NULL;
}
/***********************************************/
stackClass::~stackClass()
{
	//Receives - Nothing
	//Task - To destruct the stack
	//Returns - Nothing
	NodeType *temp;
	while (TopPtr != NULL)
	{
		temp = TopPtr;
		TopPtr = TopPtr->next;
		delete temp;
	}
}
/************************************************/
string stackClass::infixToPostfix(string s, ofstream& fout)
{
	//Receives - string infix expression and output file
	//Task - converts infix expression to postfix expression
	//Returns - string Postfix Expression
	stackClass st;
	int k = 0;
	int l = s.length();
	string ns;// postfix expression is saved here
	fout << setw(30) << "CONVERSION DISPLAY" << endl;
	fout << "Infix Expression" << setw(25) << "Postfix Expression" << setw(25)
		<< "Stack Contents" << endl;
	fout << setw(65) << "(Top to Bottom)" << endl;
	fout << s << setw(25) << "Empty" << setw(25) << "Empty" << endl;
	incLine();// Increases Line each time a line is inserted in output file
	incLine(); incLine(); incLine();
	for (int i = 0; i < l; i++)
	{		
			// If the scanned character is an operand, add it to output string.
			if (isdigit(s[i]))
			{
				ns += s[i];
				//Printing the Infix Expression
				if (k == s.length())
				{
					for (int f = 0; f < k - 4; f++)
					{
						fout << " ";
					}
					fout << "Empty";
				}
				else
				{
					for (int f = 0; f <= k; f++)
					{
						fout << " ";
					}
					for (int j = k; j < s.length(); j++)
					{
						fout << s[j];
					}
					k++;
				}
				fout << setw(20);
				//Printing the Postfix Expression
				fout << ns << setw(20);
				//Printing the stack
				if (st.IsEmpty())
				{
					fout << "Empty" << endl;
					incLine();//lineCounter++;
				}
				else
				{
					fout << st.printSt(fout);
					fout << endl;
					incLine();
				}
			}
		// If the scanned character is an ‘(‘, push it to the stack .
			else if (s[i] == '(')
			{
				char c = '(';
				st.Push(c);
				//Printing the Infix Expression
				if (k == s.length())				
				{
					for (int f = 0; f < k - 4; f++)
					{
						fout << " ";
					}
					fout << "Empty";
				}
				else
				{
					for (int f = 0; f <= k; f++)
					{
						fout << " ";
					}
					for (int j = k; j < s.length(); j++)
					{
						fout << s[j];
					}
					k++;
				}
				//Printing the postfix expression
				fout << setw(20);
				if (ns.length() == 0)
				{
					fout << "Empty" << setw(16);
				}
				else
				{
					fout << ns << setw(20);
				}
				//Printing the stack
				if (st.IsEmpty())
				{
					fout << "Empty" << endl;
					incLine();//lineCounter++;
				}
				else
				{
					fout << st.printSt(fout);
					fout << endl;
					incLine(); //lineCounter++;
				}
			}
		// If the scanned character is an ‘)’, pop and to output string from the stack
			// until an ‘(‘ is encountered.
			else if (s[i] == ')')
		{
			while (st.getTop() != NULL && st.RetrieveTop() != '(')		
			{
				char c = st.RetrieveTop();
				st.Pop();
				ns += c;
			}
			if (st.RetrieveTop() == '(')
			{
				char c = st.RetrieveTop();
				st.Pop();
			}
			//Printing the Infix Expression
			if (k == s.length())
			{
				for (int f = 0; f < k - 4; f++)
				{
					fout << " ";
				}
				fout << "Empty";
			}
			else
			{
				for (int f = 0; f <= k; f++)
				{
					fout << " ";
				}
				for (int j = k; j < s.length(); j++)
				{
					fout << s[j];
				}
				k++;
			}
			fout << setw(20);
			//Printing the Postfix Expression
			fout << ns << setw(20);
			if (st.IsEmpty())
			{
				fout << "Empty" << endl;
				incLine();
			}
			//Printing the stack
			else
			{
				fout << st.printSt(fout);
				fout << endl;
				incLine();
			}
		}
		//If an operator is scanned		
			else
		{
			//Checks the Precedence of the operators
			while ((st.getTop() != NULL) && (prec(s[i]) <= prec(st.RetrieveTop
			())))
			{
				char c = st.RetrieveTop();
				st.Pop();
				ns += c;
			}
			st.Push(s[i]);
			//Printing the Infix Expression
			if (k == s.length())
			{
				for (int f = 0; f < k - 4; f++)
				{
					fout << " ";
				}
				fout << "Empty";
			}
			else
			{
				for (int f = 0; f <= k; f++)
				{
					fout << " ";
				}
				for (int j = k; j < s.length(); j++)
				{
					fout << s[j];
				}
				k++;
			}
			fout << setw(20);
			//Print PostFix
			fout << ns << setw(20);
			//Print the stack
			if (st.IsEmpty())
			{
				fout << "Empty" << endl;
				incLine();// lineCounter++;
			}
			else
			{
				fout << st.printSt(fout);
				fout << endl;
				incLine();// lineCounter++;
			}
		}
		
	}
	//Pop all the remaining elements from the stack
	while (!st.IsEmpty())
	{
		char c = st.RetrieveTop();
		st.Pop();
		ns += c;
	}
	//Print the Infix expression
	if (k == s.length())
	{
		for (int f = 0; f < k - 4; f++)
		{
			fout << " ";
		}
		fout << "Empty";
	}
	else
	{
		for (int f = 0; f < k; f++)
		{
			fout << " ";
		}
		for (int j = k; j <= s.length(); j++)
		{
			fout << s[j];
		}
		k++;
	}
	//Print Postfix expression
	fout << setw(20) << ns << setw(20);
	//Print the stack
	if (st.IsEmpty())
	{
		fout << "Empty" << endl;
		incLine();
	}
	else
	{
		fout << st.printSt(fout);
		fout << endl;
		incLine();
	}
	return ns;
}
/******************************************/
int stackClass::incLine()
{
	//Receives - Nothing
   //Task - Nothing
   //Returns - increases lineCounter by 1 and returns it 
		return ++lineCounter;
}
/******************************************/
void stackClass::printline(ofstream &fout, int ln)
{
	//Receives - Nothing
	//Task - print extra line so that each output had seperate page
	//Returns - Nothing
	int line = ln;
	for (int lnt = line; lnt <= 49; lnt++)
	{
		fout << endl;
	}
}
/*****************************************************/
void stackClass::Header(ofstream& fout)
{
	//Receives - the outfile file
	//Task - Prints the output preamble
	//Returns - Nothing
	fout << setw(30) << "Rishika Swarnkar";
	fout << setw(17) << "CSC 36000";
	fout << setw(15) << "Section 11" << endl;
	fout << setw(30) << "Spring 2018";
	fout << setw(17) << "Assignment #4" << endl;
	fout << setw(35) << "--------------------------------------";
	fout << setw(35) << "-------------------------------------- " << endl <<
		endl;
	incLine(); incLine(); incLine(); incLine(); incLine(); incLine();
	incLine(); incLine();
	return;
}
/************* END OF FUNCTION HEADER ***************************/
//****************************************************************
/************* FUNCTION FOOTER *********************************/
void stackClass::Footer(ofstream& fout)
{
	//Receives - the outfile file
	//Task - Prints the output preamble
	//Returns - Nothing
	fout << endl;
	fout << setw(35) << "------------------------------" << endl;
	fout << setw(35) << "| END OF PROGRAM OUTPUT |" << endl;
	fout << setw(35) << "-------------------------------" << endl;
	incLine();
	incLine(); incLine(); incLine();
	return;
}
//************END OF FUNCTION FOOTER***********************
void stackClass::resetLinecounter()
{
	//Receives - Nothing
	//Task - Reset the line counter to Zero
	//Returns - Nothing
	lineCounter = 0;
}
/*******************************************/
int stackClass::evaluate(string ns, ofstream &fout)
{
	//Receives - The Infix string and outfile object
	//Task - To evalute the infix function
	//Returns - Integer
	fout << endl;
	fout << setw(30) << "EVALUTION DISPLAY" << endl;
	fout << "Infix EXPRESSION" << setw(55) << "Stack Contents" << endl;
	fout << setw(60) << "(Top to Bottom)" << endl;
	stack<int> sol;// stack for the calculations
	int i = 0;
	int u = 0;
	int soln[30];// array to print the stack
	fout << ns << setw(50) << "Empty" << endl;
	incLine(); incLine(); incLine(); incLine(); incLine();
	for (int g = 0; g < ns.length(); g++)
	{
		//Printing the Infix Expression
		u++;
		if (u == ns.length())
		{
			fout << "Empty";
		}
		for (int h = 0; h < u; h++)
		{
			fout << " ";
		}
		for (int j = u; j < ns.length(); j++)
		{
			fout << ns[j];
		}
		fout << setw(50);
		//if a digit is scanned
		if (isdigit(ns[g]))
		{
			char tempC = ns[g];
			int y;
			y = atoi(&tempC);// changes from char to int			
				soln[i] = y;// Array for printing the stack
			sol.push(y);
			for (int d = 0; d <= i; d++)
			{
				fout << soln[d];
			}
			i++;
			fout << endl;
			incLine();
		}
		else
		{
			// evaluate if scanned item is not digit
			int num1, num2;
			char temp = ns[g];
			int p;// saves the value of the operation
			if (!sol.empty())
			{
				num1 = sol.top();
				sol.pop();
			}
			if (!sol.empty())
			{
				num2 = sol.top();
				sol.pop();
			}
			if (temp == '*')
			{
				p = num2 * num1;
			}
			else if (temp == '+')
			{
				p = num2 + num1;
			}
			else if (temp == '/')
			{
				if (num1 != 0)
				{
					p = num2 / num1;
				}
			}
			else if (temp == '-')
			{
				p = num2 - num1;
			}
			sol.push(p);
			i = i - 2;
			soln[i] = p;
			//Printing the solution stack
				if (sol.empty())
				{
					fout << "Empty" << endl;
					incLine();
				}
				else
				{
					for (int d = 0; d <= i; d++)
					{
						fout << soln[d];
					}
					i++;
					fout << endl;
					incLine();
				}
		}
	}
	return sol.top();
}
/*********************************************/
void stackClass::printExpression(string ns, int ans, ofstream &fout)
{
	//Receives - string expression, int answer evaluted, output file
	//Task - Prints the original n expression and answer
	//Returns - nothing
	fout << "The Original Expression and The answer: " << endl;
	fout << ns << " = " << ans;
	incLine(); incLine();
}
/*******************************************/
bool stackClass::IsEmpty()
{
	//Receives - Nothing
	//Task - To check if the stack is empty
	//Returns - bool
	return (TopPtr == NULL);
}
/******************************************/
bool stackClass::IsFull()
{
	//Receives - Nothing
	//Task - To check if the stack if full
	//Returns - bool
	NodeType *p;
	p = new NodeType;
	if (p == NULL)
	{
		delete p;
		cout << "Out of Memory. " << endl;
		return true;
	}
	return false;
}
/*********************************************/
int stackClass::prec(char c)
{
	//Receives - A char
	//Task - Check the precedence of the char/operators
	//Returns - Nothing
	if (c == '^')
		return 3;
	else if (c == '*' || c == '/')
		return 2;
	else if (c == '+' || c == '-')
		return 1;
	else
		return -1;
}
/*********************************************/
bool stackClass::printSt(ofstream &fout)
{
	//Receives - A output file
	//Task - Print the stack from top to bottom
	//Returns - bool
	if (IsEmpty())
	{
		cout << " Print operation failed! " << endl;
		return false;
	}
	// create node for
	NodeType *p;
	p = new NodeType;
	p = TopPtr; //rear;//top
	while (p != NULL)
	{
		fout << p->data;
		p = p->next;
	}
	return true;
}
/**********************************/
char stackClass::RetrieveTop()
{
	//Receives - Nothing
	//Task - Check if the stack is empty if not then return data of top of the stack
	//Returns - Nothing
	if (IsEmpty())
	{
		cout << "Stack is Empty. " << endl;
		return '0';
	}
	else
	{
		return TopPtr->data;
	}
}
/********************************************/
char stackClass::RetrieveRear()
{
	//Receives - Nothing
	//Task - Check if the stack is empty if not
	// then return data of Rear of the stack
	//Returns - Nothing
	if (IsEmpty())
	{
		cout << "Stack is Empty. " << endl;
		return '0';
	}
	else
	{
		return rear->data;
	}
}
/*****************************************/
void stackClass::Push(char p)
{
	//Receives - A char
	//Task - Add to the Stack
	//Returns - Nothing
	if (IsFull())
	{
		cout << " Push operation failed! " << endl;
		return;
	}
	NodeType * temp = new NodeType;
	temp->data = p;
	temp->next = NULL;
	if (TopPtr == NULL)
	{
		TopPtr = temp;
		rear = temp;
	}
	else if (rear == TopPtr)
	{
		temp->next = TopPtr;
		TopPtr = temp;
	}
	else
		
	{
		temp->next = TopPtr;
		TopPtr = temp;
	}
}
/**************************************************/
bool stackClass::Pop()
{
	//Receives - Nothing
	//Task - Pop the first element of the stack
	//Returns - NodeType structure
	NodeType *p;
	NodeType var;
	if (IsEmpty())
	{
		cout << " Stack is empty. " << endl;
		cout << " Pop Operation Failed. " << endl;
		NodeType p1;
		p1.data = '0';
		return false;
	}
	var.data = TopPtr->data; // Save data in the first node
	p = TopPtr;
	TopPtr = TopPtr->next; // Adjust Stack Top
	return true;
}
/************************************/
NodeType * stackClass::getTop()
{
	//Receives - Nothing
	//Task - Nothing
	//Returns - Top Pointer
	return TopPtr;
}
/******** THE END ***************************/