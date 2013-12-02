#ifndef DIRECTED_ACYCLIC_GRAPH_H
#define DIRECTED_ACYCLIC_GRAPH_H

/*****************************************
 * UW User ID:  d73kim	
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Fall) 2013
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "ece250.h"
#include "Exception.h"
#include <queue>
#include <limits>
#include <iostream>

//template <typename Type>
class Directed_acyclic_graph {
	private:
		int size; //size of the 2x2 array
		int countEdge; //counting the edge
		int *inDegreeArr; //in-degree array
		int *outDegreeArr; //out-degree array
		double *priorityArr; //priority array
		bool **array; // 2x2 array
		double findMin(double*) const; // method that finds priority

	public:
		Directed_acyclic_graph( int = 10 );
		Directed_acyclic_graph( Directed_acyclic_graph const & );
		~Directed_acyclic_graph();

		void swap( Directed_acyclic_graph & );
		Directed_acyclic_graph &operator = ( Directed_acyclic_graph );

		int in_degree( int ) const;
		int out_degree( int ) const;
		int edge_count() const;
		bool adjacent( int, int ) const;
		bool connected( int, int ) const;
		void topological_sort() const;

		bool set_priority( int, double );
		bool insert_edge( int, int );
		void clear_edges();
		void reset_priorities();

	friend std::ostream &operator << ( std::ostream &, Directed_acyclic_graph const & );
};


//There are no templates in this project, make a use of std::queue<Type> container


void Directed_acyclic_graph::swap( Directed_acyclic_graph &dag ) {
	// Swap all your member variables
}

/*
	Constructor. initializes all the arrays, size to default, countEdge to 0
*/
Directed_acyclic_graph::Directed_acyclic_graph( int n ):
size(n),
countEdge(0),	//initially edge count is 0
inDegreeArr(new int[size]),
outDegreeArr(new int[size]),
priorityArr(new double[size]),
array(new bool*[size]){

	for(int i = 0; i < size; i++)
	{
		array[i] = new bool[size]; //making it 2-dimentional array
		inDegreeArr[i] = 0;	//setting all the indegree to 0
		outDegreeArr[i] = 0; //setting all the outdegree to 0
	}
}


/*
	Destructor. Sets the size and edge count to 0. Deleting all the arrays.
*/
Directed_acyclic_graph::~Directed_acyclic_graph(){
	size = 0;
	countEdge = 0;
	delete[] inDegreeArr;
	delete[] outDegreeArr;
	delete[] priorityArr;

	for (int i = 0; i < size; ++i)
	{
		delete array[i];
	}

	delete[] array;
	//array = nullptr;
	

}

/*
	Copy constructor. Copying all the arrays.
*/
Directed_acyclic_graph::Directed_acyclic_graph(Directed_acyclic_graph const &copyArray) :
size(copyArray.size),
countEdge(copyArray.countEdge),
inDegreeArr(new int[size]),
outDegreeArr(new int[size]),
priorityArr(new double[size]),
array(new bool*[size])
{
	for (int i = 0; i < size; i++)
	{
		//copying arrays index by index
		inDegreeArr[i] = copyArray.inDegreeArr[size];
		outDegreeArr[i] = copyArray.outDegreeArr[size];
		priorityArr[i] = copyArray.priorityArr[size];
		array[i] = new bool[size];

		for (int j = 0; j < size; j++)
		{
			array[i][j] = copyArray.array[i][j];
		}
	}
}

//Assignment Operator =
Directed_acyclic_graph &Directed_acyclic_graph::operator = ( Directed_acyclic_graph rhs ) {
	swap( rhs );

	return *this;
}

/*
	in_degree() method. Checks if the i is less than 0 or greater than the size and if they are,
	we throw illegal_argument() error. Else, we return indegree of the index i by returning the 
	indegree array of index i. 

*/
int Directed_acyclic_graph::in_degree( int i ) const{
	if(i < 0 || i > size)
	{
		throw illegal_argument();
	}
	return inDegreeArr[i];
}

/*
	out_degree() method. Checks if the i is less than 0 or greater than the size and if they are,
	we throw illegal_argument() error. Else, we return outdegree of the index i by returning the 
	outdegree array of index i. 

*/
int Directed_acyclic_graph::out_degree( int i ) const{
	if(i < 0 || i > size)
	{
		throw illegal_argument();
	}
	return outDegreeArr[i];
}

/*
	edge_count() method. Returns the number of edges
*/
int Directed_acyclic_graph::edge_count() const{
	return countEdge;
}

/*
	adjacent() method. Checks if i or j are less than 0 or greater than the size and if any of them are,
	we throw illegal_argument() error. I check if they are adjacent and if they are, I return true else, false.
*/
bool Directed_acyclic_graph::adjacent( int i, int j) const{
	if((i < 0 || i > size) || (j < 0 || j > size))
	{
		throw illegal_argument();
	}

	if(array[i][j])
	{
		return true;
	}
	else
	{
		return false;
	}
}

/*
	connected() method. I created a queue and push i into the queue.
	while my queue is not empty, I create a temporary integer variable(tmp) and 
	tmp is equal to the first element in queue. Then I pop queue and chech to see if it is 
	equal to j, then i return true. This means i = j, just one vertex. 
	If i is not equal to j, I traverse my 2 dimensional array to check if they are true which means they are connected.
*/
bool Directed_acyclic_graph::connected( int i, int j) const{


	std::queue<int>queue;
	queue.push(i);
	while(!queue.empty())
	{
		int tmp = queue.front();
		queue.pop();
		if(tmp == j)
		{
			return true;
		}
		else
		{
			for(int k=0; k<size; k++)
			{
				if(array[tmp][k])
				{
					queue.push(k);
					//return true?
				}
			}
		}
	}
	return false;
}

/*
	topological_sort() method.
*/
void Directed_acyclic_graph::topological_sort() const{
	int *tmpArr = new int[size];
	double *sortArr = new double[size];

	for(int k = 0; k < size; k++)
	{
		tmpArr[k] = inDegreeArr[k];
	}

	for(int p =0; p < size; p++)
	{
		for(int k = 0; k < size; k++)
		{
			if(tmpArr[k] == 0)
			{
				sortArr[k] = priorityArr[k];
			}	
			else
			{
				sortArr[k] = std::numeric_limits<double>::infinity();
			}
		}

		int index = findMin(sortArr);
		std::cout<<"-";
		std::cout<<index;
		//std::cout<<"-";

		tmpArr[index] = -1;	



	for (int n = 0; n < size; n++)
	{
		if(adjacent(index, n))
		{
			  tmpArr[n]--;
		}
	}
	}


//std::numeric_limits<double>::infinity();

	delete [] tmpArr;
	delete [] sortArr;
}

/*
	findMin() method.
*/
double Directed_acyclic_graph::findMin( double* sortArr) const{
	double minValue = std::numeric_limits<double>::infinity();
	int index;

	for(int k = 0; k < size; k++)
	{
		if(sortArr[k] < minValue)
		{
			minValue = sortArr[k];
			index = k;
		}
	}


	return index;
}


//Mutators
/*
	set_priority() method.
*/
bool Directed_acyclic_graph::set_priority( int i, double priority ){
	for(int k = 0; k<size; k++)
	{
		if(priorityArr[k] == priority)
		{
			return false;
		}
	}

	priorityArr[i] = priority;
	return true;
}

/*
	insert_edge() method. Checks if i or j are less than 0 or greater than the size and if any of them are,
	we throw illegal_argument() error. Check if i and j are connected and if they are, returns false. 
	Else, I turn the index of i and j in my 2-dimensional array to true, increment edge count, indegree array, outdegree
	and return true.
*/
bool Directed_acyclic_graph::insert_edge( int i, int j ){
	if((i < 0 || i > size) || (j < 0 || j > size))
	{
		throw illegal_argument();
	}

	if(connected(j,i))
	{
		return false;
	}

	else 
	{
		array[i][j] = true;
		countEdge++;
		inDegreeArr[j]++;
		outDegreeArr[i]++;
		return true;
	}


}

/*
	clear_edge() method. Resets both indegree and outdegree array to 0.
	sets edge count back to 0
*/
void Directed_acyclic_graph::clear_edges(){
	for(int i = 0; i < size; i++)
	{
		inDegreeArr[i] = 0;
		outDegreeArr[i] = 0;
		for(int j = 0; j<size; j++)
		{
			array[i][j] = 0;
		}
	}
	countEdge = 0;
}

/*
	reset_priorities()) method. Resets the priority array back to what it was.
*/
void Directed_acyclic_graph::reset_priorities(){
	for(int i = 0; i<size; i++)
	{
		priorityArr[i] = i;
	}
}


// whatever you want...

// You can modify this function however you want:  it will not be tested

std::ostream &operator << ( std::ostream &out, Directed_acyclic_graph const &list ) {
	out << "#";

	return out;
}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif