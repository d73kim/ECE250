#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/*****************************************
 * UW User ID:  uwuserid
 * Submitted for ECE 250
 * Semester of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename Type>
class Double_hash_table {
	private:
		int count;
		int power;
		int array_size;
		int mask;
		Type *array;
		state *occupied;

		int h1( Type const & ) const;
		int h2( Type const & ) const;

	public:
		Double_hash_table( int = 5 );
		~Double_hash_table();
		int size() const;
		int capacity() const;
		double load_factor() const;
		bool empty() const;
		bool member( Type const & ) const;
		Type bin( int ) const;

		void print() const;

		void insert( Type const & );
		bool remove( Type const & );
		void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator << ( std::ostream &, Double_hash_table<T> const & );
};

// Constructor
template<typename Type>
Double_hash_table<Type>::Double_hash_table( int m ):
count( 0 ), 
power( m ),
array_size( 1 << power ),
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new state[array_size] ) {

	for ( int i = 0; i < array_size; ++i ) {
		occupied[i] = EMPTY;
	}
}

// Destructor
template<typename Type>
Double_hash_table<Type>::~Double_hash_table(){
	clear();
}

// Accessors
// size() method
template<typename Type>
int Double_hash_table<Type>::size() const{
	return count;
}

// capacity() method
template<typename Type>
int Double_hash_table<Type>::capacity() const{
    return array_size;
}

// load_factor() method
template<typename Type>
double Double_hash_table<Type>::load_factor() const{
    return static_cast<double>(count)/array_size;
}

// empty() method
template<typename Type>
bool Double_hash_table<Type>::empty() const{
	if (count == 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

// member() method
template<typename Type>
bool Double_hash_table<Type>::member( Type const &) const{

}

// bin() method
template<typename Type>
Type Double_hash_table<Type>::bin(int) const{

}

// print() method
template<typename Type>
void Double_hash_table<Type>::print() const{

}

// Mutators
// insert() method
template<typename Type>
void Double_hash_table<Type>::insert( Type const & ){

}

// remove() method
template<typename Type>
bool Double_hash_table<Type>::remove( Type const & ){

}

// clear() method
template<typename Type>
void Double_hash_table<Type>::clear(){
	
}


template <typename T>
std::ostream &operator << ( std::ostream &out, Double_hash_table<T> const &hash ) {
	for ( int i = 0; i < hash.capacity(); ++i ) {
		if ( hash.occupied[i] == EMPTY ) {
			out << "- ";
		} else if ( hash.occupied[i] == DELETED ) {
			out << "x ";
		} else {
			out << hash.array[i] << ' ';
		}
	}

	return out;
}

#endif