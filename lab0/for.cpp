#include <iostream>
using namespace std;

int main() {
	const int N = 64;
	
	for ( int j = 0; j >= -2; --j) {
		cout << "Values resulting in " << j << ":" << endl;

		for( int i = -N; i <= N; ++i) {
			if ( i /6 == j) {
				cout << i << endl;
			}
		}
	}

	return 0;
	
}
