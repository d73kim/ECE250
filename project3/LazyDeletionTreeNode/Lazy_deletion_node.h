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

template <typename Type>
Lazy_deletion_node<Type>::Lazy_deletion_node( Type const &obj ):
element( obj ),
left_tree( nullptr ),
right_tree( nullptr ),
erased( false ) {
	// does nothing
}

//accessors
template<typename Type>
Lazy_deletion_node<Type>::Lazy_deletion_node<Type> *left() const{
	return left_tree;
}

template<typename Type>
Lazy_deletion_node<Type>::Lazy_deletion_node<Type> *right() const{
	return right_tree;
}

template<typename Type>
Type Lazy_deletion_node<Type>::retrieve() const{
	return element;
}

template<typename Type>
int Lazy_deletion_node<Type>::height() const{
	int leftHeight, rightHeight, maxHeight;

	if(this == nullptr)
	{
		return -1;
	}
	else
	{
		leftHeight = left()->height();
		rightHeight = right()->height();
		maxHeight = std::max(leftHeight, rightHeight);
	}
	
	return maxHeight + 1;
}

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

template<typename Type>
bool Lazy_deletion_node<Type>::erase(Type const &obj){
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
		if(obj < element)
		{
			return left()->erase(obj);

		}
		else if(obj>element)
		{
			return right()->erase(obj);	
		}

	}

}

template<typename Type>
void Lazy_deletion_node<Type>::clear(){
	left_tree ->clear() 
	delete left_tree;

	right_tree ->clear()
	delete right_tree;
}

template<typename Type>
void Lazy_deletion_node<Type>::clean(Lazy_deletion_node *&ptr_to_this){
	if(this == nullptr)
	{
		return;
	}

	//std::pair
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
			std::pair<Type,bool> result = left_tree -> left();
			if (result.second)
			{
				element = result.first;
				erased = false;
				left_tree -> erase(element);
			}
		}
	}

	right_tree -> clean();
	left_tree -> clean();

	if(erased)
	{
		Lazy_deletion_node = nullptr;
		delete this;
	}
}


// Your implementation here

#endif