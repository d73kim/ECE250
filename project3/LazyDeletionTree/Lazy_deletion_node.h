#ifndef LAZY_DELETION_NODE_H
#define LAZY_DELETION_NODE_H

/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By  submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "ece250.h"
#include "Exception.h"
#include <utility>

#define nullptr 0

template <typename Type>
class Lazy_deletion_tree;

template <typename Type>
class Lazy_deletion_node {
	private:
		Type element;
		Lazy_deletion_node<Type> *left_tree;
		Lazy_deletion_node<Type> *right_tree;
		bool erased;

	public:
		Lazy_deletion_node( Type const & = Type() );

		Lazy_deletion_node<Type> *left() const;
		Lazy_deletion_node<Type> *right() const;
		Type retrieve() const;
		int height() const;
		std::pair<Type, bool> front() const;
		std::pair<Type, bool> back() const;
		bool member( Type const & ) const;

		bool insert( Type const & );
		bool erase( Type const & );
		void clear();
		void clean( Lazy_deletion_node *& );

	friend class Lazy_deletion_tree<Type>;
};

// Constructor.
template <typename Type>
Lazy_deletion_node<Type>::Lazy_deletion_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
erased( false ) {
	// does nothing
}

//accessors

/*
	left() method. Returning a pointer to the left subtree.
*/
template<typename Type>
Lazy_deletion_node<Type> *Lazy_deletion_node<Type>::left() const{
	return left_tree;
}

/*
	right() method. Returning a pointer to the right subtree.
*/
template<typename Type>
Lazy_deletion_node<Type> *Lazy_deletion_node<Type>::right() const{
	return right_tree;
}

/*
	retrieve() method. Returns the element.
*/
template<typename Type>
Type Lazy_deletion_node<Type>::retrieve() const{
	return element;
}

/*
	height() method. Returns the height of the subtree with
	this node as the root. Here, I am using the standard library funtion
	std::max to find out the maximum height from the root node and adding
	one once I find out the height.
*/
template<typename Type>
int Lazy_deletion_node<Type>::height() const{
	int Height;

	if(this == nullptr)
	{
		return -1;
	}
	else
	{
		Height = std::max(left()->height(), right()->height());
	}
	
	return Height + 1;
}

/*
	member() method. If this is nullptr, return false. Otherwise 
	We have a couple of conditions to go through. First to see if the 
	argument is less then the object, we go down the left subtree
	and return true. Second condition is if the argument is greater than
	the element, we go down the right subtree and return true.
*/
template<typename Type>
bool Lazy_deletion_node<Type>::member( Type const &obj ) const{
	if (this == nullptr)
	{
		return false;
	}
	else
	{
		if(obj<element)
		{
			return left()->member(obj);
		}
		else if(obj>element)
		{
			return right()->member(obj);
		}
		else
		{
			return true;
		}

	}
}	

template <typename Type>
std::pair<Type, bool> Lazy_deletion_node<Type>::front() const {
	if ( this == nullptr ) {
		return std::pair<Type, bool>( Type(), false );
	}

	std::pair<Type, bool> result = left()->front();

	if ( result.second ) {
		return result;
	}

	if ( !erased ) {
		return std::pair<Type, bool>( retrieve(), true );
	}

	result = right()->front();

	if ( result.second ) {
		return result;
	}

	return std::pair<Type, bool>( Type(), false );
}


template <typename Type>
std::pair<Type, bool> Lazy_deletion_node<Type>::back() const {
	if ( this == nullptr ) {
		return std::pair<Type, bool>( Type(), false );
	}

	std::pair<Type, bool> result = right()->back();

	if ( result.second ) {
		return result;
	}

	if ( !erased ) {
		return std::pair<Type, bool>( retrieve(), true );
	}

	result = left()->back();

	if ( result.second ) {
		return result;
	}

	return std::pair<Type, bool>( Type(), false );

}


//mutators
/*
	insert() method. 
	If the obj is already in the node and if it has been erased, 
	we tag it as not erased and return true.
	Else we just return false and do nothing.

	If the obj is smaller than the element and the node thats pointed by
	the left_tree is nullptr, then we create a new node and insert the 
	obj there. Then we return true. If the node thats pointed by
	left_tree is not nullptr, we just insert. 

	If the obj is greater than the element and the node thats pointed by
	the right_tree is nullptr, then we create a new node and insert the 
	obj there. Then we return true. If the node thats pointed by
	left_tree is not nullptr, we just insert. 
*/
template<typename Type>
bool Lazy_deletion_node<Type>::insert(Type const &obj){
	if (obj == element)
	{
		if(erased)
		{
			erased = false;
			return true;
		}
		else
		{
			return false;		
		}
	}
	else
	{
		if(obj < element)
		{
			if(left_tree == nullptr)
			{
				left_tree = new Lazy_deletion_node<Type>(obj);
				return true;
			}

				return left()->insert(obj);
		}


		else if(obj > element)
		{
			if(right_tree == nullptr)
			{
				right_tree = new Lazy_deletion_node<Type>(obj);
				return true;
			}

				return right() -> insert(obj);
		}
	}
}

/*
	erase() method. Algorithm of this method is similar with
	insert() method except I don't need to create a new node when
	the node pointed by left_node or right_node is nullptr. When they
	are nullptr, all I need to do is return false. When they are not
	nullptr, I just need to find the node and erase.
*/
template<typename Type>
bool Lazy_deletion_node<Type>::erase(Type const &obj){
	if(obj == element)
	{
		if(erased)
		{
			return false;
		}
		else
		{
			erased = true;
			return true;
		}
	}
	else
	{
		if(obj < element)
		{
			if (left_tree == nullptr)
			{
				return false;
			}

			return left()->erase(obj);

		}
		else if(obj>element)
		{
			if (right_tree == nullptr)
			{
				return false;
			}
			return right()->erase(obj);	
		}

	}

}
/*
	clear() method. if this is nullptr, return. Else, I need to
	delete on both subtrees and delete this node.
*/
template<typename Type>
void Lazy_deletion_node<Type>::clear(){
	if(this == nullptr)
	{
		return;
	}

	left_tree ->clear(); 
	right_tree ->clear();
	delete this;
}
/*
*/
template<typename Type>
void Lazy_deletion_node<Type>::clean(Lazy_deletion_node *&ptr_to_this){
	if(this == nullptr)
	{
		return;
	}

	if(erased)
	{
		std::pair<Type,bool> result = right_tree -> front();

		if(result.second) //checking to see if the result is valid
		{
			element = result.first;
			erased = false;
			right_tree -> erase(element);
		}
		else
		{
			std::pair<Type,bool> result = left_tree -> back();
			if (result.second)
			{
				element = result.first;
				erased = false;
				left_tree -> erase(element);
			}
		}
	}

	right_tree -> clean(right_tree);
	left_tree -> clean(left_tree);

	if(erased)
	{
		ptr_to_this = nullptr;
		delete this;
	}
}

/*
	DIFFERENCE BETWEEN CLEAN CLEAR

*/




// Your implementation here

#endif