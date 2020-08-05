#ifndef List_h
#define List_h

#include<iostream>
#include"Node.h"
using namespace std;
template<typename dataType>
class List{
	public:
	Node<dataType> * head;
	List();
	~List();
	
	void insertStart(dataType d);
	void insertLast(dataType d);
	void insertAt(dataType d,int i);

	void removeStart();
	void removeLast();
	void remove(int i);

	void printList();
	int size();
	int search(dataType d);
};

#endif