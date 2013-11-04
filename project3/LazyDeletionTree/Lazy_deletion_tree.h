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

template <typename Type>
Lazy_deletion_tree<Type>::Lazy_deletion_tree():
root_node( nullptr ),
count( 0 ) {
	// Only initializes member variables
}

//destructor
template <typename Type>
Lazy_deletion_tree<Type>::~Lazy_deletion_tree(){
	clear();
}


//accessors
//empty method
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

//size method
template<typename Type>
int Lazy_deletion_tree<Type>::size() const {
	return count;
}


template<typename Type>
int Lazy_deletion_tree<Type>::height() const {
	return root_node -> height();
}


template<typename Type>
bool Lazy_deletion_tree<Type>::member( Type const &obj ) const{
	return root_node -> memeber(obj);

}

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

template <typename Type>
void Lazy_deletion_tree<Type>::breadth_first_traversal() const {
	if ( root_node == nullptr ) {
		return;
	}

	// Read up on the STL queue at http://www.cplusplus.com/reference/queue/queue/
	std::queue< Lazy_deletion_node<Type> *> queue;

	queue.push( root_node );

	while ( !queue.empty() ) {
		// do something...
	}
}

//mutators

template<typename Type>
bool Lazy_deletion_tree<Type>::insert(Type const & ){
	root_node -> insert();


}

template<typename Type>
bool Lazy_deletion_tree<Type>::erase(Type const & ){


	if(obj == element)
	{
		if(erased)
		{
			erased = false;
			return true;
		}
		else
		{
			erased = true;
			return false;
		}
	}
	else
	{
		return false;

	}

	if(root_node == nullptr)
	{
		return false;
	}
	else
	{
		erase(root_node);
	}



}

template<typename Type>
void Lazy_deletion_tree<Type>::clear() {
	root_node -> clear();
	root_node = nullptr;

}

template<typename Type>
void Lazy_deletion_tree<Type>::clean() {
	if (erased)
	{
		root_node -> clean();
		root_node = nullptr;
	}
}

// Your implementation here

#endif
