//*************** PROGRAM IDENTIFICATION*****************************
//*                                                                  *
//* PROGRAM FILE NAME: Source.cpp Assisgnment #:4					 *
//*                                                                  *
//* PROGRAM AUTHOR                     ______________________        *
//*                                        Rishika Swarnkar          *
//*                                                                  *
//*COURSE: CSC 36000 1             	      DATE:April 16,2018         *
//*                                                                  *
/********************************************************************/
//*************** PROGRAM DESCRIPTION ********************************
//*                                                                   *
//*  PROCESS:This program will take a mathematical expression in INFIX*
//*notation, convert it to POSTFIX notation, and then evaluate POSTFIX*
//*notation form of the expression.The program employs stacks with    *
//* pointers.							                              *
//* INPUT:  Input for this program will consist of an unknown number  *
//* of lines.Each line will contain a mathematical expression in INFIX*
//* notation.                                                         *
//*Using stacks, the program converts the INFIX expression to POSTFIX *
//*notation and then evaluate the POSTFIX expression.                 *
//*OUTPUT: Output for each expression is to appear on a separate page.*
//*Output is to consist of 3 phases.								  *
//*They are the conversion phase,evaluation phase and expression phase*
//*A running display of the contents of the INFIX buffer,             *
//*the POSTFIX buffer, and the stack.                                 *
//* USER DEFINED MODULES :											  *
//*stackClass():set private pointers to NULL						  *
//*~stackClass():To destruct the stack                                *
//*infixToPostfix(string,ofstream&): converts infix expression to     *
//*								postfix expression					  *
//*incLine(): increases lineCounter by 1 and returns it               *
//*printline(ofstream&,int): print extra line so that each output had *
//*                  seperate page                                    *
//*Header(ofstream&):Prints the output Header preamble                *
//*Footer(ofstream& fout): Prints the output Footer preamble          *
//*resetLinecounter(int):Reset the line counter to Zero               *
//*evaluate(string,ofstream &):To evalute the infix function          * 
//*printExpression(string,int,ofstream &): Prints the original        *
//*               expression and answer                               *
//*IsEmpty():checks if the stack is empty                             *
//*IsFull():checks if the stack if full                               *
//*prec(char)  - checks the precedence of the operators               *
//*printSt(ofstream &): Print the stack from top to bottom            *
//*RetrieveTop(): Check if the stack is empty if not then return data *
//*            of top of the stack                                    *
//*RetrieveRear(): Check if the stack is empty if not then return data*
//*                   of Rear of the stack                            *
//*Push(char):Adds to the Stack                                       *
//*Pop():Pop the first element of the stack                           *
//*getTop():Returns the Top Pointer                                   *
/**********************************************************/
#include "stackClass.h"
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cstdlib>
#include <stack>
using namespace std;
int main()
{
	stackClass expression;
	string exp;
	ifstream infile;
	infile.open("stack_in.txt");// open the input file
	infile >> exp;
	ofstream fout;
	fout.open("evalutionFinal.txt"); // Open the output file
	expression.Header(fout);
	do
	{
		string s = expression.infixToPostfix(exp, fout);
		int answer = expression.evaluate(s, fout);
		expression.printExpression(exp, answer, fout);
		int ln = expression.incLine();
		expression.printline(fout, ln);
		expression.resetLinecounter();
		infile >> exp;
	} while (exp != "X");
	expression.Footer(fout);//print output footer
	infile.close();//close input file
	fout.close();//close output file
	system("pause");
	return 0;
}
