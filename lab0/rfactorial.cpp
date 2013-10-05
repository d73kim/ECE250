#include "exception.h"

#include <iostream>
using namespace std;
int rfactorial ( int n ) {
	if ( n == 0) {
		return 1;
	} else if ( n > 0 ){
		return n * rfactorial ( n - 1 );
	} else {
	   // ( n < 0 )
		throw division_by_zero();
	}
}

int  main() {
	while ( true ) {
	
		int n;
		cout << "Enter a number: ";
		cin >> n;

	try {
		int nfact = rfactorial( n );
		cout << n << "! = " << nfact<< endl;
	} catch ( division_by_zero) {
		cout << n << "! = undefined" << endl;
	} catch ( overflow ) {
		cout << n << "! > 4294967295" << endl;	
}
}
	return 0;
}

