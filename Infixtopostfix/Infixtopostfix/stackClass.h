#ifndef STACKCLASS_H
#define STACKCLASS_H
#include<stack>
#include <iostream>
#include <string>
using namespace std;
struct NodeType
{
	char data;//char data;
			  //CAN BE EXPNDED TO FIT SITUATION      
	NodeType * next;
};
// define the stack class StackClass       
class stackClass
{
public:
	stackClass();
	~stackClass();
	string infixToPostfix(string s, ofstream &);
	int prec(char ch);
	void printline(ofstream &fout, int ln);
	void Push(char);
	bool printSt(ofstream &fout);
	NodeType* getTop();
	bool Pop();
	int incLine();
	int evaluate(string ns, ofstream &fout);
	char RetrieveTop();
	char RetrieveRear();
	bool IsEmpty();
	bool IsFull();
	void printExpression(string ns, int ans, ofstream &fout);
	void Header(ofstream& fout);
	void Footer(ofstream& fout);
	void resetLinecounter();
private:
	NodeType * TopPtr;
	NodeType *rear;
	int lineCounter;
};
#endif
