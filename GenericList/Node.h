#ifndef Node_h
#define Node_h

#include<iostream>
#include<stdlib.h>
using namespace std;

template<typename dataType>
class Node{
	private:
		dataType data;
		Node * next;
	public:
		Node * createNode(dataType d);
		~Node();
		Node * getNext();
		void setNext(Node * newNode);

		dataType getData();
		void setData(dataType d);
};

#endif
