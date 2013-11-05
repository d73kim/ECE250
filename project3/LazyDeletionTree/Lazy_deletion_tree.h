#ifndef LAZY_TREE_H
#define LAZY_TREE_H

#include <queue>
#include "Lazy_deletion_node.h"

/*****************************************
 * UW User ID:  uwuserid
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
	comments
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
	comments
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
	comments
*/
template <typename Type>
void Lazy_deletion_tree<Type>::breadth_first_traversal() const {
	if ( root_node == nullptr ) {
		return;
	}

	// Read up on the STL queue at http://www.cplusplus.com/reference/queue/queue/
	// create a queue?
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
	insert() method. 
*/
template<typename Type>
bool Lazy_deletion_tree<Type>::insert(Type const & obj){
	bool flag = false;

	if (empty())
	{
		if (root_node == nullptr)
		{
			root_node = new Lazy_deletion_node<Type>(obj);
			count++;
			return true;
		}
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
	clear() method. Deleting all nodes in the tree.
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
