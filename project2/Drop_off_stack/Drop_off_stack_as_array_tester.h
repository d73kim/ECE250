/*************************************************
* Drop_off_stack_as_array
* A class for testing a drop-off stack-as-arrays.
*
* Author:  Douglas Wilhelm Harder
* Copyright (c) 2006-8 by Douglas Wilhelm Harder.  All rights reserved.
*
* DO NOT EDIT THIS FILE
*************************************************/

#ifndef _DROP_OFF_STACK_AS_ARRAY_H
#define _DROP_OFF_STACK_AS_ARRAY_H

#include "Exception.h"
#include "Tester.h"
#include "Drop_off_stack_as_array.h"

#include <iostream>

template <typename Type>
class Drop_off_stack_as_array_tester :public Tester< Drop_off_stack_as_array<Type> > {
	using Tester< Drop_off_stack_as_array<Type> >::object;
	using Tester< Drop_off_stack_as_array<Type> >::command;

public:
	Drop_off_stack_as_array_tester(Drop_off_stack_as_array<Type> *obj = 0) :Tester< Drop_off_stack_as_array<Type> >(obj) {
		// empty
	}

	void process();
};

/****************************************************
* void process()
*
* Process the current command.  For drop-off stacks-as-arrays, these include:
*
*  Constructors
*
*   new             constructor     create a stack with the default array size
*   new: n          constructor     create a stack with an array size of n
*
*  Accessors
*
*   size n          size            the size equals n
*   empty b         empty           the result is the boolean value b
*   top n           top             n is the first element in the stack
*   top!            top             the underflow exception is thrown
*
*  Mutators
*
*   push n          push            the element can be pushed (always succeeds)
*   pop n           pop             the top can be pop
*   pop!            pop             the underflow exception is thrown
*
*  Others
*
*   assign          operator =      assign this stack to a new stack
*   summary                         prints the amount of memory allocated
*                                   minus the memory deallocated
*   details                         prints a detailed description of which
*                                   memory was allocated with details
*
****************************************************/

template <typename Type>
void Drop_off_stack_as_array_tester<Type>::process() {
	if (command == "new") {
		object = new Drop_off_stack_as_array<Type>();
		std::cout << "Okay" << std::endl;
	}
	else if (command == "new:") {
		int n;
		std::cin >> n;
		object = new Drop_off_stack_as_array<Type>(n);
		std::cout << "Okay" << std::endl;
	}
	else if (command == "size") {
		// check if the size equals the next integer read

		int expected_size;

		std::cin >> expected_size;

		int actual_size = object->size();

		if (actual_size == expected_size) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << "Failure in size(): expecting the value '" << expected_size << "' but got '" << actual_size << "'" << std::endl;
		}
	}
	else if (command == "empty") {
		// check if the empty status equals the next boolean read

		bool expected_empty;

		std::cin >> expected_empty;

		bool actual_empty = object->empty();

		if (actual_empty == expected_empty) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << "Failure in empty(): expecting the value '" << expected_empty << "' but got '" << actual_empty << "'" << std::endl;
		}
	}
	else if (command == "top") {
		// checks if the first integer in the stack equals the next integer read

		Type expected_top;

		std::cin >> expected_top;

		Type actual_top = object->top();

		if (actual_top == expected_top) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << "Failure in top(): expecting the value '" << expected_top << "' but got '" << actual_top << "'" << std::endl;
		}
	}
	else if (command == "top!") {
		// top of an empty stack - catch an exception

		Type actual_top;

		try {
			actual_top = object->top();
			std::cout << "Failure in top(): expecting to catch an exception but got '" << actual_top << "'" << std::endl;
		}
		catch (underflow) {
			std::cout << "Okay" << std::endl;
		}
		catch (...) {
			std::cout << "Failure in top(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	}
	else if (command == "push") {
		// push the next integer read to the front of the stack

		Type obj;

		std::cin >> obj;

		object->push(obj);
		std::cout << "Okay" << std::endl;
	}
	else if (command == "pop") {
		// pop the first integer from the stack

		Type expected_popped_element;

		std::cin >> expected_popped_element;

		Type actual_popped_element = object->pop();

		if (actual_popped_element == expected_popped_element) {
			std::cout << "Okay" << std::endl;
		}
		else {
			std::cout << "Failure in pop(): expecting the value '" << expected_popped_element << "' but got '" << actual_popped_element << "'" << std::endl;
		}
	}
	else if (command == "pop!") {
		// pop from an empty stack - catch an exception

		Type actual_popped_element;

		try {
			actual_popped_element = object->pop();
			std::cout << "Failure in pop(): expecting to catch an exception but got '" << actual_popped_element << "'" << std::endl;
		}
		catch (underflow) {
			std::cout << "Okay" << std::endl;
		}
		catch (...) {
			std::cout << "Failure in pop(): expecting an underflow exception but caught a different exception" << std::endl;
		}
	}
	else if (command == "clear") {
		object->clear();

		std::cout << "Okay" << std::endl;
	}
	else if (command == "assign") {
		Drop_off_stack_as_array<Type> *new_object = new Drop_off_stack_as_array<Type>();

		*new_object = *(object);

		std::cout << "Okay" << std::endl;

		Drop_off_stack_as_array_tester<Type> tester(new_object);

		tester.run();
	}
	else if (command == "cout") {
		std::cout << *object << std::endl;
	}
	else {
		std::cout << command << ": Command not found." << std::endl;
	}
}
#endif