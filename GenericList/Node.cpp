#include<iostream>
#include<stdlib.h>
#include"Node.h"

template<typename dataType>
Node<dataType> *Node<dataType> :: createNode(dataType d)
{
	Node<dataType> * newNode;
	newNode = (Node<dataType> *)malloc(sizeof(Node<dataType>));

	if(newNode == NULL){
		cout<<"Memory was not allocated" ; 
		return 0;
	}

	newNode -> next = NULL;
	newNode -> data = d;
	return newNode;
}

template<typename dataType>
Node<dataType> :: ~Node()
{
	next = NULL;
	delete next;
}

template<typename dataType>
void Node<dataType> :: setData(dataType d)
{
	data = d;
}

template<typename dataType>
dataType Node<dataType> :: getData()
{
	return data;
}

template<typename dataType>
void Node<dataType> :: setNext(Node * newNode)
{
	next = newNode;
}

template<typename dataType>
Node<dataType> * Node<dataType> :: getNext()
{
	return next;
}
