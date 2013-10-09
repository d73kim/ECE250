#ifndef SINGLE_LIST_H
#define SINGLE_LIST_H

/*****************************************
* UW User ID:  uwuserid
* Submitted for ECE 250
* Department of Electrical and Computer Engineering
* University of Waterloo
* Calender Term of Submission:  (Fall) 2013
*
* By submitting this file,  I affirm that
* I am the author of all modifications to
* the provided code.
*****************************************/

#include "ece250.h"
#include "Single_node.h"
#include "Exception.h"
#include <iostream>

#define NULLVARIATE_CONSTRUCTOR

template <typename Type>
class Single_list {
private:
	Single_node<Type> *list_head;
	Single_node<Type> *list_tail;
	int node_count;

public:
	Single_list();
	Single_list(Single_list const &);
	~Single_list();

	// Accessors

	int size() const;
	bool empty() const;

	Type front() const;
	Type back() const;

	Single_node<Type> *head() const;
	Single_node<Type> *tail() const;

	int count(Type const &) const;

	// Mutators

	void swap(Single_list &);
	Single_list &operator = (Single_list const &);

	void push_front(Type const &);
	void push_back(Type const &);

	Type pop_front();

	int erase(Type const &);

	// Friends

	template <typename T>
	friend std::ostream &operator << (std::ostream &, Single_list<T> const &);
};

template <typename Type>
Single_list<Type>::Single_list() :
list_head(0),
list_tail(0),
node_count(0) {
	// empty constructor
}

/* 
copy constructor creates new instances of the linked list
need to deep copy, not shallow copy. 
making a use of push_back() 
*/
template <typename Type>
Single_list<Type>::Single_list(Single_list<Type> const &list) :
list_head(0),
list_tail(0),
node_count(0) {

	for (Single_node<Type> *node = list.head(); node != 0; node = node->next())
	{
		push_back(node->retrieve());
	}
	
}

//destructor
template <typename Type>
Single_list<Type>::~Single_list() {
	while (!empty())
	{
		pop_front();
	}
}

// returns size of the list
template <typename Type>
int Single_list<Type>::size() const {
	return node_count;
}

// returns true if the list is empty, else it returns false
template <typename Type>
bool Single_list<Type>::empty() const {

	if (list_head == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// throws an underflow if the list is empty
// else it returns the object that is stored by the head pointer 
template <typename Type>
Type Single_list<Type>::front() const {

	if (empty())
	{
		throw underflow();
	}
	else
	{
		return head()->retrieve();
	}
	
}

// throws an underflow if the list is empty
// else it returns the object that is stored by the tail pointer 
template <typename Type>
Type Single_list<Type>::back() const {
	
	if (empty())
	{
		throw underflow();
	}
	else
	{
		return tail()->retrieve();
	}
}

// returns the head pointer
template <typename Type>
Single_node<Type> *Single_list<Type>::head() const {

	return list_head;
}

// returns the tail pointer
template <typename Type>
Single_node<Type> *Single_list<Type>::tail() const {
	
	return list_tail;
}

/* 
counting the number of nodes that are equal to the argument 
in the list and returns the number of nodes
*/
template <typename Type>
int Single_list<Type>::count(Type const &obj) const {

	int count = 0;
	Single_node<Type> *currentNode = head();

	while (currentNode)
	{

		if (currentNode->retrieve() == obj)
		{
			count++;
		}
		currentNode = currentNode -> next();
	}

	return count;
}

template <typename Type>
void Single_list<Type>::swap(Single_list<Type> &list) {
	std::swap(list_head, list.list_head);
	std::swap(list_tail, list.list_tail);
	std::swap(node_count, list.node_count);
}

template <typename Type>
Single_list<Type> &Single_list<Type>::operator = (Single_list<Type> const &rhs) {
	Single_list<Type> copy(rhs);

	swap(copy);

	return *this;
}

/* 
if the list is empty, the node that have just been created becomes head of the list 
as well as tail of the list
inserting a new node in the beginning(head) of the list
*/
template <typename Type>
void Single_list<Type>::push_front(Type const &obj) {

	Single_node<Type> *newNode = new Single_node<Type>(obj, head());

	if (empty())
	{
		list_head = newNode;
		list_tail = head();
	}
	else
	{
		list_head = newNode;
	}

	node_count++;
}
/*
if the list is empty, the node that have just been created becomes tail of the list
as well as head of the list
inserting a new node at the end(tail) of the list
*/
template <typename Type>
void Single_list<Type>::push_back(Type const &obj) {

	Single_node<Type> *newNode = new Single_node<Type>(obj, 0);

	if (empty())
	{
		list_tail = newNode;
		list_head = list_tail;
	}
	else
	{
		list_tail->next_node = newNode;
		list_tail = newNode;
	}
	node_count++;

}

// taking out the head node of the list and update the head as next node of the head originally
// throws an underflow if the list is empty
template <typename Type>
Type Single_list<Type>::pop_front() {

	Type tmp;
	if (empty())
	{
		throw underflow();
	}
	else
	{
		tmp = list_head->retrieve();
		Single_node<Type> *tmpNode = list_head;
		list_head = tmpNode->next();
		if (size() == 1)
		{
			list_tail = list_head;
		}
		delete tmpNode;
		node_count--;
		return tmp;
	}
}

//Deleting the nodes in the linked list that contains the object equal to the argument

template <typename Type>
int Single_list<Type>::erase(Type const &obj) {
	
	int deleteCount = 0;
	Single_node<Type> *currentNode = head();
	Single_node<Type> *previousNode = nullptr;

	int counter = size();

	for (int i = 0; i < counter; i++)
	{
		if (currentNode->retrieve() == obj)
		{
			//case 1. considering if the head node contains the object equal to the argument
			if (currentNode == head())
			{
				pop_front();
				currentNode = head();
			}
			//case 2. considering if the tail node contains the object equal to the argument
			else if (currentNode == tail()) 
			{
				Single_node<Type> *tempNode = currentNode;
				list_tail = previousNode;
				currentNode = previousNode;
				currentNode->next_node = nullptr;
				delete tempNode;
				node_count--;
			}
			//case 3. considering if body node contains the object equal to the argument
			else
			{
				previousNode->next_node = currentNode->next();
				Single_node<Type> *tempNode = currentNode;

				delete tempNode;

				currentNode = currentNode->next();
				node_count--;
			}

			deleteCount++;
		}
		else
		{
			previousNode = currentNode;
			currentNode = currentNode->next();
		}
	}

	return deleteCount;
}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator << (std::ostream &out, Single_list<T> const &list) {
	for (Single_node<T> *ptr = list.head(); ptr != 0; ptr = ptr->next()) {
		out << "->" << ptr->retrieve();
	}

	out << "->0";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif
