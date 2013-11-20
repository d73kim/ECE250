#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/*****************************************
 * UW User ID:  d73kim
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2013
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
    
    int h1( Type const & ) const; //hash function h1
    int h2( Type const & ) const; //hash function h2
    
public:
    Double_hash_table( int = 5 ); //constructor
    ~Double_hash_table(); //destructor
    int size() const; //size() method
    int capacity() const; //capacity method
    double load_factor() const; //load_factor() method
    bool empty() const; //empty() method
    bool member( Type const & ) const; //member() method
    Type bin( int ) const; //bin() method. ask about what this is suppoesed to do
    
    void print() const; //print method. not getting tested on this
    
    void insert( Type const & ); //insert() method
    bool remove( Type const & ); //remove() method
    void clear(); //clear() method
    
    // Friends
    
    template <typename T>
    friend std::ostream &operator << ( std::ostream &, Double_hash_table<T> const & );
};

// Constructor
// array size of 32 by default
template<typename Type>
Double_hash_table<Type>::Double_hash_table( int m ):
count( 0 ), //initially count is 0
power( m ), //m = 5
array_size( 1 << power ),
mask( array_size - 1 ),
array( new Type[array_size] ),
occupied( new state[array_size] ) {
    
    for ( int i = 0; i < array_size; ++i ) {
        occupied[i] = EMPTY;
    }
}

/*
   Destructor. calls clear() method. Deleting the array and occupied array.
*/
template<typename Type>
Double_hash_table<Type>::~Double_hash_table(){
    clear();
    delete [] array;
    delete [] occupied;
}

// Accessors
/*
    size() method. Returns the number of elements currently stored
    in the hash table.
*/
template<typename Type>
int Double_hash_table<Type>::size() const{
    return count;
}

/*
    capacity() method. Returns the number of bins in the hash table by
    retuning the array_size.
*/
template<typename Type>
int Double_hash_table<Type>::capacity() const{
    return array_size;
}

/*
    load_factor() method. Returns the load factor of the hash table. This casts
    to double.
*/ 
template<typename Type>
double Double_hash_table<Type>::load_factor() const{
    return static_cast<double>(count)/array_size;
}

/*
    empty() method. Returns true if the count is 0, else return false.
*/
template<typename Type>
bool Double_hash_table<Type>::empty() const{
    if (count == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* 
    member() method. This method is to check if the object is currently
    stored in the hash table. If the obj is stored in the hash table and marked as
    OCCUPIED, it returns true else, return false. 
*/
template<typename Type>
bool Double_hash_table<Type>::member( Type const &obj) const{
    int hash1 = h1(obj);
    int hash2 = h2(obj);
    
    for (int i = 0; i < array_size; i++)
    {
        int hashValue = (hash1 + (i*hash2))%array_size;
        
        if (array[hashValue] == obj && occupied[hashValue] == OCCUPIED)
        {
            return true;
        }
    }
    
    return false;
}

/*
    bin() method. This method returns the entry in bin n.
*/
template<typename Type>
Type Double_hash_table<Type>::bin(int n) const{
    return Type(array[n]);
}

// print() method
template<typename Type>
void Double_hash_table<Type>::print() const{
    // dont need
}

/*
    h1() method. This is the primary hash function. We first cast the obj into integer,
    then take the mod of obj by the array_size and save it into the variable named bin.
    Check to see if the bin is less than 0. If it is less than 0, we add array_size to the bin. 
    Returns bin.
*/ 
template<typename Type>
int Double_hash_table<Type>::h1( Type const &obj ) const {
    int h1 = static_cast<int>(obj);
    int bin = h1%array_size;
    
    if (bin < 0)
    {
        bin += array_size;
    }
    
    return bin;
}

/*
    h2() method. This is the secondary hash function. We first cast the obj in integer.
    We have second hash function that was given, save this into the variable named "bin".
    Returns bin.

*/
template<typename Type>
int Double_hash_table<Type>::h2( Type const &obj ) const {
    int h2 = static_cast<int>(obj);
    int bin = (h2/array_size)%array_size;
    
    if (bin%2 == 0)
    {
        bin += 1;
    }
    
    if (bin < 0)
    {
        bin += array_size;
    }
    
    return bin;
}

// Mutators
/*
    insert() method. If the array is already full, than we throw overflow().
    We call member() method to check if the obj we want to insert is already there, 
    and if it is, we do nothing and return.
    We calculate hash1 and hash2 using h1() and h2() above. 
    We calculate hashValue using h1 and h2 to find the index the obj is supposed to be inserted.
    If obj we want to insert is already there and marked as DELETED, we mark it as OCCUPIED, increment the count and return true.
    If occupied array is not marked as OCCIPIED, we insert the obj, mark it as OCCUPIED, increment count and return.
     
*/
template<typename Type>
void Double_hash_table<Type>::insert( Type const &obj ){
    if (count == array_size)
    {
        throw overflow();
    }
    
    if(member(obj))
    {
        return;
    }
    
    int hash1 = h1(obj);
    int hash2 = h2(obj);
    
    for (int i = 0; i < array_size; i++)
    {
        int hashValue = (hash1 + (i*hash2))%array_size;
        //this is for testing
        //std::cout<< obj <<" "<< hashValue << " " << array[hashValue] << " " << occupied[hashValue]<< std::endl;
        if (array[hashValue] == obj && occupied[hashValue] == DELETED)
        {
            occupied[hashValue] = OCCUPIED;
            count++;
            return;
        }
        
        if (occupied[hashValue] != OCCUPIED)
        {
            array[hashValue] = obj;
            occupied[hashValue] = OCCUPIED;
            count++;
            return;
        }
    }
    
    return;
    
}

/*
    remove() method. Similar logic from insert() method applies. Once we find the proper position(index) but
    the obj we want to insert is already in there and if it is marked as OCCUPIED, we mark it as DELETED,
    decrement the count and return True. Else we return false.
*/
template<typename Type>
bool Double_hash_table<Type>::remove( Type const &obj ){
    int hash1 = h1(obj);
    int hash2 = h2(obj);
    
    for (int i = 0; i < array_size; i++)
    {
        int hashValue = (hash1 + (i*hash2))%array_size;
        
        if (array[hashValue] == obj && occupied[hashValue] == OCCUPIED)
        {
            occupied[hashValue] = DELETED; 
            count--;
            return true;
        }
    } 
    return false;
}

/*
    clear() method. deleting every element in the array. once we delete, we mark it as EMPTY. 
    Setting the count to be zero
*/
template<typename Type>
void Double_hash_table<Type>::clear(){
    for (int i = 0; i < array_size; i++)
    {
        occupied[i] = EMPTY;
    }
    
    count = 0;
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