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
	// this is test comment
	


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

// constructor. I Made ihead and itail to point at the same entry. 
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
	copy constrctor. looping through the entire array and copying the element.
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
	destructor.
	setting ihead, array_capacity, itail and entry_count to be 0 and delete the array
*/
template <typename Type>
Dynamic_queue_as_array<Type>::~Dynamic_queue_as_array() {
	delete [] array;
	ihead = 0;
	itail = 0;
	entry_count = 0;
	array_capacity = 0;
}

/*
	returing the current number of element in the array
*/

template <typename Type>
int Dynamic_queue_as_array<Type>::size() const {
	return entry_count;
}

/*
	returning the capacity of the array.
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
	copying the element in the new array index by index then enqueue the new object. updating the array to be new array created.
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

		Type *tempArray = array;
		//delete [] tempArray;

		array = doubleArray;

		array_capacity = array_capacity * 2;
		array[itail] = obj;
		++entry_count;
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
	throws underflow() if the queue is empty. A several scenarios to consider. First of all, when the array is full,
	I set ihead to go back to the first index of the array which is 0. If the entry_count is less than
	quarter of the array capacity after dequeue the object, I create a new array that is half the size of 
	original array. After that, I simply just copy the object over to the halved array. 
	One thing to keep in mind is when the ihead index is at the last index of the array, I need to make it go to the
	first index of the array(4th if statement).
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

		if (ihead == array_capacity)
		{
			ihead = 0;
		}


		if (entry_count < array_capacity / 4)
		{
			Type *halvedArray = new Type[array_capacity / 2];

			q = ihead;

			for (int i = 0; i < array_capacity/4; i++)
			{
				if (q > array_capacity-1)
				{
					q -= (array_capacity-1);
				}

				halvedArray[i] = array[q];

				q++;
			}

	 		array_capacity = array_capacity/2;
			ihead = 0;
			itail = array_capacity - 1;

			Type *tempArray = array;
			delete [] tempArray;

			array = halvedArray;
		}

		return tmp;

	}
}
//deleting every element in the array. 
template <typename Type>
void Dynamic_queue_as_array<Type>::clear() {

	entry_count = 0;
	array_capacity = 0;

	for (int i = 0; i < array_capacity; i++)
	{
		array[i] = 0;
	}

	ihead = 0;
	itail = 0;

	delete [] array;
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