#ifndef DYNAMIC_QUEUE_AS_ARRAY_H
#define DYNAMIC_QUEUE_AS_ARRAY_H

/*****************************************
* UW User ID:  d73kim
* Submitted for ECE 250
* Semester of Submission:  (Fall) 2013
*
* By submitting this file, I affirm that
* I am the author of all modifications to
* the provided  code.
*****************************************/

#include "ece250.h"
#include "Exception.h"

template <typename Type>
class Dynamic_queue_as_array {
private:
	int initial_capacity;
	int array_capacity;
	Type *array;
	int ihead;
	int itail; 
	int entry_count;


public:
	Dynamic_queue_as_array(int = 10);
	Dynamic_queue_as_array(Dynamic_queue_as_array const &);
	~Dynamic_queue_as_array();

	Type head() const;
	int size() const;
	bool empty() const;
	int capacity() const;

	void swap(Dynamic_queue_as_array &);
	Dynamic_queue_as_array &operator = (Dynamic_queue_as_array);
	void enqueue(Type const &);
	Type dequeue();
	void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator << (std::ostream &, Dynamic_queue_as_array<T> const &);
};

// constructor. Made ihead and itail to point at the same entry. 
// They are both pointing at the index 0. 
template <typename Type>
Dynamic_queue_as_array<Type>::Dynamic_queue_as_array(int n) :
initial_capacity(std::max(n,1)),
array_capacity(initial_capacity),
array(new Type[initial_capacity]),
ihead(0),
itail(0),
entry_count(0) {
	
}


/*
	copy constrctor. looping through the entire array and copying the element
	I have an access to the queue arreay
*/

template <typename Type>
Dynamic_queue_as_array<Type>::Dynamic_queue_as_array(Dynamic_queue_as_array const &queue) :
initial_capacity(queue.initial_capacity),
array_capacity(queue.array_capacity),
array(new Type[array_capacity]),
ihead(queue.ihead),
itail(queue.itail),
entry_count(queue.entry_count) {

	for (int i = 0; i < entry_count; i++)
	{
		array[ihead - i] = queue.array[ihead - i];
	}

}


/*
	setting ihead, itail and entry_count to 0 and delete the array
*/
template <typename Type>
Dynamic_queue_as_array<Type>::~Dynamic_queue_as_array() {
	delete[] array;
	ihead = 0;
	itail = 0;
	entry_count = 0;
}

/*
	returing the current number of element in the array
*/
template <typename Type>
int Dynamic_queue_as_array<Type>::size() const {
	return entry_count;
}

/*
	returning the capacity of the array. capacity is 10 by default.
	However I can set it to for example, size of 3 in the beginnning
*/
template <typename Type>
int Dynamic_queue_as_array<Type>::capacity() const {
	return array_capacity;
}

// returns true if the array is empty else return false
template <typename Type>
bool Dynamic_queue_as_array<Type>::empty() const {
	if (entry_count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}

}

/*
	throws underflow() if the queue is empty
	else returns the object at the front of the queue
*/
template <typename Type>
Type Dynamic_queue_as_array<Type>::head() const {
	if (empty())
	{
		throw underflow();
	}
	else
	{
		return array[ihead];
	}
}

template <typename Type>
void Dynamic_queue_as_array<Type>::swap(Dynamic_queue_as_array<Type> &queue) {
	std::swap(initial_capacity, queue.initial_capacity);
	std::swap(array_capacity, queue.array_capacity);
	std::swap(array, queue.array);
	std::swap(ihead, queue.ihead);
	std::swap(itail, queue.itail);
	std::swap(entry_count, queue.entry_count);
}

template <typename Type>
Dynamic_queue_as_array<Type> &Dynamic_queue_as_array<Type>::operator = (Dynamic_queue_as_array<Type> rhs) {
	swap(rhs);

	return *this;
}

/*
	enqueue(push) method. object gets pushed to the back of the array.
	two scenarios to think about, when the array is full and when the array is not full.
	when the array is full, need to make another array that is doubled the size of initial array created.
	copying the element in the new array index by index. updating the array to be new array created.
	When the array is not full, I enqueue the object in the tail.
*/
template <typename Type>
void Dynamic_queue_as_array<Type>::enqueue(Type const &obj) {
	if (entry_count == array_capacity)
	{
		
		Type *doubleArray = new Type[entry_count*2];
		
		for (int i = 0; i < array_capacity; i++)
		{
			doubleArray[i] = array[i];
		}
		array = doubleArray;
		
		array[itail] = obj;
		++entry_count;
		array_capacity = array_capacity * 2;
		++itail;

	}
	else
	{
		array[itail] = obj;
		++itail;
		++entry_count;
		
	}
}

/*
	throws underflow() if the queue is empty
	else pops the object that is in the front of the queue
*/
template <typename Type>
Type Dynamic_queue_as_array<Type>::dequeue() {
	Type tmp;
	int q;

	if (empty())
	{
		throw underflow();
	}
	else
	{
		tmp = array[ihead];
		array[ihead] = 0;
		--entry_count;
		++ihead;
		if (ihead < 0)
		{
			ihead = array_capacity - 1;
		}
		if (entry_count < array_capacity / 4)
		{
			Type *rowoonArray = new Type[array_capacity / 2];

			q = ihead;

			for (int i = 0; i < array_capacity/4; i++)
			{
				q += i;
				if (q >= array_capacity - 1) {
					q = 0;
				}

				rowoonArray[i] = array[q];
			}
		}

		return tmp;

	}
}
//deleting every element in the array. 
template <typename Type>
void Dynamic_queue_as_array<Type>::clear() {
	entry_count = 0;
	ihead = itail;
}

// You can modify this function however you want:  it will not be tested

template <typename Type>
std::ostream &operator << (std::ostream &out, Dynamic_queue_as_array<Type> const &queue) {
	// I don't know how you are implementing your queue so I cannot print it.
	// If you want, you can print whatever you want here and then call cout
	// in the driver.

	// Remember to redirect to out, e.g.,
	//      out << "Hello!";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif