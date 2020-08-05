#include<iostream>
#include<stdlib.h>
#include"List.h"

template<typename dataType>
List<dataType> :: List()
{
	head = NULL;
}

template<typename dataType>
List<dataType> :: ~List()
{
	head = NULL;
	delete head;
}

template<typename dataType>
void List<dataType> :: insertStart(dataType d)
{
	Node<dataType> * newNode;
	newNode = newNode -> createNode(d);

	if(head == NULL){
		head = newNode;
		return;
	}

	newNode -> setNext(head);
	head = newNode;
	newNode = NULL;
	delete newNode;
}

template<typename dataType>
void List<dataType> :: insertLast(dataType d)
{
	Node<dataType> * newNode;
	newNode = newNode -> createNode(d);

	if(head == NULL){
		head = newNode;
		return;
	}

	Node<dataType> *tmp = head;

	while(tmp -> getNext() != NULL)
		tmp = tmp->getNext();

	tmp -> setNext(newNode);
	newNode = NULL;
	delete newNode;
}

template<typename dataType>
void List<dataType> :: insertAt(dataType d , int i)
{
	if(i < 0 || i > size()){
		cout<<"check the index passed"<<endl;
		return;
	}

	if(i == 0){
		insertStart(d);
		return;
	}

	if(i == size()){
		insertLast(d);
		return;
	}

	Node<dataType> * newNode;
	newNode = newNode -> createNode(d);
	Node<dataType> *tmp = head;
	int j=0;

	while(j < i-1){
		tmp = tmp -> getNext();
		j++;
	}

	newNode -> setNext(tmp -> getNext());
	tmp -> setNext(newNode);
	newNode = NULL;
	delete newNode;

	return;
}


template<typename dataType>
void List<dataType> :: printList()
{
	if(head == NULL)
		return;

	Node<dataType> * tmp = head;

	while(tmp != NULL){
		cout<<tmp -> getData()<<"  ";
		tmp = tmp -> getNext();
	}

	cout<<endl;
	tmp = NULL;
	delete tmp;
}

template<typename dataType>
int List<dataType> :: size()
{
	int i = 0;
	if(head == NULL) 
		return i;

	Node<dataType> * tmp = head;

	while(tmp != NULL){
		//cout<<tmp->getData()<<"\t";
		i++;
		tmp = tmp -> getNext();
	}

	tmp = NULL;
	delete tmp;
	return i;
}

template<typename dataType>
int List<dataType> :: search(dataType d)
{
	if(head == NULL)
		return -1;

	Node<dataType> * tmp = head;
	int i = 0;

	while(tmp != NULL){
		if(tmp -> getData() == d)
			return i;

		tmp = tmp -> getNext();
		i++;
	}

	tmp = NULL;
	delete tmp;
	return -1;
}

template<typename dataType>
void List<dataType> :: removeStart()
{
	if(head == NULL) 
		return;

	if(head -> getNext() == NULL){
		head = NULL;
		return;
	}

	Node<dataType> * tmp = head;
	head = tmp -> getNext();
	tmp = NULL;
	delete tmp;
	return;
}

template<typename dataType>
void List<dataType> :: removeLast()
{
	if(head == NULL)
		return;

	if(head -> getNext() == NULL){
		head = NULL;
		return;
	}

	Node<dataType> * tmp = head;
	while(tmp -> getNext() -> getNext() != NULL)	tmp = tmp -> getNext();
	tmp -> setNext(NULL);
	tmp = NULL;
	delete tmp;
	return;
}

template<typename dataType>
void List<dataType> :: remove(int i)
{
	if(head == NULL) 
		return;

	if(i < 0 || i >= size()){
		cout<<"check the index passed"<<endl;
		return;
	}

	if(i == 0){
		removeStart();
		return;
	}

	if(i == size()-1){
		removeLast();
		return;
	}

	Node<dataType> * tmp = head;
	int j=0;
	while(j < i-1){
		tmp = tmp -> getNext();
		j++;
	}
	
	Node<dataType> * tmp1 = tmp -> getNext() -> getNext();
	tmp -> setNext(tmp1);
	tmp = NULL;
	tmp1 = NULL;
	delete tmp;
	delete tmp1;
	return;
}
