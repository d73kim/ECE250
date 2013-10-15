#ifndef DROP_OFF_STACK_AS_ARRAY_H
#define DROP_OFF_STACK_AS_ARRAY_H

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

template <typename Type>
class Drop_off_stack_as_array {
	//memebers
private:

	int itop;
	int ibottom;
	int entry_count; // stack_size?
	int array_capacity;
	Type *array;

public:

	Drop_off_stack_as_array(int = 10);
	Drop_off_stack_as_array(Drop_off_stack_as_array const &);
	~Drop_off_stack_as_array();

	int size() const;
	bool empty() const;
	Type top() const;

	void swap(Drop_off_stack_as_array &);
	Drop_off_stack_as_array &operator = (Drop_off_stack_as_array);
	void push(Type const &);
	Type pop();
	void clear();

	// Friends

	template <typename T>
	friend std::ostream &operator << (std::ostream &, Drop_off_stack_as_array<T> const &);
};


template <typename Type>
Drop_off_stack_as_array<Type>::Drop_off_stack_as_array(int n)
// Constructor
:itop(-1),
ibottom(0),
entry_count(0),
array_capacity(std::max(1, n)),
array(new Type[array_capacity])
{
	// it should be in a order

}

// Copy Contructor. come back to this
template <typename Type>
Drop_off_stack_as_array<Type>::Drop_off_stack_as_array(Drop_off_stack_as_array<Type> const &stack) :
itop(stack.itop),
ibottom(stack.ibottom),
entry_count(stack.entry_count),
array_capacity(stack.array_capacity),
array(new Type[array_capacity]) {
	// The above initializations copy the values of the appropriate
	// member variables and allocate memory for the data structure; 
	// however, you must still copy the stored objects.

	// Enter your implementation here.
	for (int i = 0; i < entry_count; i++)
	{
		array[itop-i] = stack.array[itop-i];
	}
}

// Destructor
template <typename Type>
Drop_off_stack_as_array<Type>::~Drop_off_stack_as_array() {
	delete[] array;
	entry_count = 0;
	itop = -1;
	ibottom = 0;
}

template <typename Type>
int Drop_off_stack_as_array<Type>::size() const {
	return entry_count;
}

// return true if the stack is empty otherwise return false
template <typename Type>
bool Drop_off_stack_as_array<Type>::empty() const {
	if (entry_count == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// throw underflow() if the stack is empty otherwise return
// the object that is at the top of the stack
template <typename  Type>
Type Drop_off_stack_as_array<Type>::top() const {
	if (empty())
	{
		throw underflow();
	}
	else
	{

		return array[itop];
	
	}
}

template <typename Type>
void Drop_off_stack_as_array<Type>::swap(Drop_off_stack_as_array<Type> &stack) {
	std::swap(itop, stack.itop);
	std::swap(ibottom, stack.ibottom);
	std::swap(entry_count, stack.entry_count);
	std::swap(array_capacity, stack.array_capacity);
	std::swap(array, stack.array);
}

template <typename Type>
Drop_off_stack_as_array<Type> &Drop_off_stack_as_array<Type>::operator = (Drop_off_stack_as_array<Type> rhs) {
	swap(rhs);

	return *this;
}

template <typename Type>
void Drop_off_stack_as_array<Type>::push(Type const &obj) {
	/*
	note: pushing an object onto the stack can only be
	performed if the array is not full
	*/
	//full
	if (entry_count == array_capacity)
	{
		itop = ibottom;
		array[itop] = obj;
		ibottom = (ibottom + 1)%array_capacity;
	}

	else
	{
		++itop;
		array[itop] = obj;
		++entry_count;

	}
	//std::cout << *this;
}

template <typename Type>
Type Drop_off_stack_as_array<Type>::pop() {
	//std::cout << *this;
	Type tmp;
	
	if (empty())
	{
		throw underflow();
	}

	else
	{
		tmp = array[itop];
		--entry_count;
		--itop;
		if (itop < 0)
		{
			itop = array_capacity-1;
		}
		return tmp;
		
	}

}

template <typename Type>
void Drop_off_stack_as_array<Type>::clear() {
	entry_count = 0;
	itop = ibottom;

}

// You can modify this function however you want:  it will not be tested

template <typename T>
std::ostream &operator << (std::ostream &out, Drop_off_stack_as_array<T> const &stack) {
	// I don't know how you are implementing your stack so I cannot print it.
	// If you want, you can print whatever you want here and then call cout
	// in the driver.

	// Remember to redirect to out, e.g.,
	//      out << "Hello!";
	out << "itop:" << stack.itop << std::endl;
	out << "ibottom:" << stack.ibottom << std::endl;
	out << "entry count:" << stack.entry_count << std::endl;
	for (int i = 0; i < stack.array_capacity; i++)
	{
		out << i << ":" << stack.array[i] << " ";
	}
	out << std::endl;
	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif