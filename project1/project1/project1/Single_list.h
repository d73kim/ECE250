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

template <typename Type>
Single_list<Type>::Single_list(Single_list<Type> const &list) :
list_head(0),
list_tail(0),
node_count(0) {
	// copy constructor creates new instances of the linked list
	// need to deep copy, not shallow copy.
	// make a use of push_back()
	for (Single_node<Type> *node = list.head(); node != 0; node = node->next())
	{
		//std::cout << node << std::endl;
		push_back(node->retrieve());

	}
	
}

template <typename Type>
Single_list<Type>::~Single_list() {
	//destructor
	while (!empty())
	{
		pop_front();
	}
}

template <typename Type>
int Single_list<Type>::size() const {
	// returns size of the list
	return node_count;
}

template <typename Type>
bool Single_list<Type>::empty() const {
	// returns true if the list is empty, else it returns false
	if (list_head == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

template <typename Type>
Type Single_list<Type>::front() const {
	// throws an underflow if the list is empty
	// else returns the object that is stored by the head pointer 
	if (empty())
	{
		throw underflow();
	}
	else
	{
		return head()->retrieve();
	}
	
}

template <typename Type>
Type Single_list<Type>::back() const {
	// enter your implementation here
	if (empty())
	{
		throw underflow();
	}
	else
	{
		return tail()->retrieve();
	}
}

template <typename Type>
Single_node<Type> *Single_list<Type>::head() const {
	// returns the head pointer
	return list_head;
}

template <typename Type>
Single_node<Type> *Single_list<Type>::tail() const {
	// returns the tail pointer
	return list_tail;
}

template <typename Type>
int Single_list<Type>::count(Type const &obj) const {
	// creates a new integer type variable names count that is 0
	int count = 0;
	// creating a new pointer named currentNode that is pointing to the head of the list
	Single_node<Type> *currentNode = head();
	// while currentNode contains some objects
	while (currentNode)
	{
		// check to see if the object in the currentNode is equal to the obj
		// if it is equal, then we increment the count by 1
		if (currentNode->retrieve() == obj)
		{
			count++;
		}
		// move to the next node
		currentNode = currentNode -> next();
	}

	// returning the number of node
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

template <typename Type>
void Single_list<Type>::push_front(Type const &obj) {
	// creating a new node that is pointing... come back to this
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
	// incrementing the node counter
	node_count++;
}

template <typename Type>
void Single_list<Type>::push_back(Type const &obj) {
	// enter your implementation here
	Single_node<Type> *newNode = new Single_node<Type>(obj, 0);


	if (empty())
	{
		list_tail = newNode;
		list_head = list_tail;
	}
	else
	{
		// used to be, list_tail-> next() = newNode; why doesn't work?
		list_tail->next_node = newNode;
		//newNode = list_tail-> next();
		list_tail = newNode;
		// checking to see if the list is already empty and if it is, head pointer is set to the new node
	}
	// incrementing the node counter
	node_count++;

}

template <typename Type>
Type Single_list<Type>::pop_front() {
	// come back to this
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
//this is test comment
template <typename Type>
int Single_list<Type>::erase(Type const &obj) {
	// come back to this
	int deleteCount = 0;
	Single_node<Type> *currentNode = head();
	Single_node<Type> *previousNode = nullptr;

	int counter = size();

	for (int i = 0; i < counter; i++)
	{
		if (currentNode->retrieve() == obj)
		{
			if (currentNode == head())
			{
				pop_front();
				currentNode = head();
			}
			else if (currentNode == tail()) 
			{
				Single_node<Type> *tempNode = currentNode;
				list_tail = previousNode;
				currentNode = previousNode;
				currentNode->next_node = nullptr;
				delete tempNode;
				node_count--;
			}
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
