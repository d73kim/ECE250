#ifndef LAZY_TREE_H
#define LAZY_TREE_H

#include <queue>
#include "Lazy_deletion_node.h"

/*****************************************
 * UW User ID:  d73kim
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By  submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#define nullptr 0

template <typename Type>
class Lazy_deletion_tree {
	private:
		Lazy_deletion_node<Type> *root_node;
		int count;

	public:
		Lazy_deletion_tree();
		~Lazy_deletion_tree();

		bool empty() const;
		int size() const;
		int height() const;
		Type front() const;
		Type back() const;
		bool member( Type const & ) const;
		void breadth_first_traversal() const;

		bool insert( Type const & );
		bool erase( Type const & );
		void clean();
		void clear();
};

/*
	Constructor
*/
template <typename Type>
Lazy_deletion_tree<Type>::Lazy_deletion_tree():
root_node( nullptr ),
count( 0 ) {
	// Only initializes member variables
}

/*
	Destructor. Calling clear() method to delete all nodes in the tree.
*/
template <typename Type>
Lazy_deletion_tree<Type>::~Lazy_deletion_tree(){
	clear();
}


//accessors
/*
	empty() method. Returns true if the tree is empty.
	Returns false if the tree is not empty.
*/
template<typename Type>
bool Lazy_deletion_tree<Type>::empty() const {
	if(count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
	size() method. Returns the number of nodes in the tree without
	counting the nodes are the tagged as erased.
*/
template<typename Type>
int Lazy_deletion_tree<Type>::size() const {
	return count;
}

/*
	height() method. Returns the height of the tree.
*/
template<typename Type>
int Lazy_deletion_tree<Type>::height() const {
	return root_node -> height();
}

/*
	member() method. returns if the argument is in the tree
	and not tagged as erased. False otherwise.
*/
template<typename Type>
bool Lazy_deletion_tree<Type>::member( Type const &obj ) const{
	return root_node -> member(obj);

}

/*
	front() method. I create a pair called result using standard library function. 
	I check if there is a node that can be replaced in the right subtree. if there isn't,
	throw underflow(). Otherwise if we have the node that contains proper value, we 
	return that result
*/
template<typename Type>
Type Lazy_deletion_tree<Type>::front() const{
	std::pair<Type,bool> result = root_node->front();

	if(!result.second)
	{
		throw underflow();
	}
	else
	{
		return result.first;
	}

}

/*
	back() method. I create a pair called result using standard library function. 
	I check if there is a node that can be replaced in the left subtree. if there isn't,
	throw underflow(). Otherwise if we have the node that contains proper value, we 
	return that result
*/
template<typename Type>
Type Lazy_deletion_tree<Type>::back() const{
	std::pair<Type,bool> result = root_node->back();

	if(!result.second)
	{
		throw underflow();
	}
	else
	{
		return result.first;
	}

}

/*
	breadth first traversal() method implemented using standard library function queue.
	If the root node is nullptr, we return. Else, we create a queue named queue. We are going
	to first push the root node to the queue. We go in a loop while the queue is not empty, 
	we are going to create a pointer that points to the head of the queue. Since we enqueued
	a root node to the queue, now we need to pop it in order to begin the BFT. Then we cheack if
	the left subtree childred are there, and if they are, then we push them into the queue. Same 
	thing for the right subtree as well. If an object is marked as erased, an "x " is printed 
	immediately following the object, otherwise only a single space " " is printed.
*/
template <typename Type>
void Lazy_deletion_tree<Type>::breadth_first_traversal() const {
	if ( root_node == nullptr ) {
		return;
	}

	// Read up on the STL queue at http://www.cplusplus.com/reference/queue/queue/
	// create a queue
	std::queue< Lazy_deletion_node<Type> *> queue;

	queue.push( root_node );

	while ( !queue.empty() ) {
		// head of the queue
		Lazy_deletion_node<Type> *ptr = queue.front();
		// pop the root node in the queue and inserting the children node
		queue.pop();

		if(ptr -> left_tree != nullptr)
		{
			queue.push(ptr -> left_tree);
		}
		if(ptr -> right_tree != nullptr)
		{
			queue.push(ptr -> right_tree);
		}
					
		if(ptr -> erased)
		{
			std::cout << ptr -> retrieve() << "x "; 
		}
		else
		{
			std::cout << ptr -> retrieve() << " "; 
		}

	}
}

//mutators

/*
	insert() method. we first check to see if the root node is nullptr. If the root node is nullptr
	this means that the tree is empty. Then we go ahead and make a new node and insert object. increment the count, return true.
	Otherwise we have a boolean variable flag and it's initially false. if we insert the object, the flag
	becomes true. We increment and return true only if the flag is true otherwise we return false. 
*/
	
template<typename Type>
bool Lazy_deletion_tree<Type>::insert(Type const & obj){
	bool flag = false;

	if (root_node == nullptr)
	{
		root_node = new Lazy_deletion_node<Type>(obj);
		count++;
		return true;
	}
	
	else
	{
		flag = root_node -> insert(obj);
		if (flag)
		{
			count++;
			return true;
		}
		else
		{
			return false;
		}
	}
}

/*
	erase() method. Returns false if the tree is empty. Otherwise it
	decrements the count of the node, finds the node that matches argument
	and erase it.
*/
template<typename Type>
bool Lazy_deletion_tree<Type>::erase(Type const & obj){
	if (empty())
	{
		return false;
	}
	else
	{
		count--;
		return root_node-> erase(obj);
	}
}

/*
	clear() method. Deleting all nodes in the tree. Making the root node to be nullptr.
	sets the count to be zero.
*/
template<typename Type>
void Lazy_deletion_tree<Type>::clear() {
	root_node -> clear();
	root_node = nullptr;
	count = 0;

}

/*
	clean() method. cleaning out all the erased nodes.
*/
template<typename Type>
void Lazy_deletion_tree<Type>::clean() {
	root_node -> clean(root_node);
}

// Your implementation here

#endif
