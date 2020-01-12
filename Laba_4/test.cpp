/*#include <iostream>
#include <cstdio>
#include <iomanip>


using namespace std;

int a[10000];

int main () {
	for (int i = 0; i < 10000; ++i)
		a[i] = i < 5000 ? 1 : -1 ;
	int sum;
	unsigned int x;
	// volatile long long t = rdtscp(&x);
	for (int i = 0; i < 10000; ++i)
		if (a[i] >= 0)
			sum += a[i];
	// t = rdtscp(&8) - t;
	// printf("%d", t);
}
*/
