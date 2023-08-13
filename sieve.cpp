#include <iostream>
#include <vector>

using namespace std;


int main() {
	int n;
	cin >> n;
	vector<long long >sieve(n, true);
	for (int i=2; i*i<=n; i++) {
		if (sieve[i]) {
			for (int j=i; j*i<n; j++) {
				sieve[j*i] = 0;
			}
		}
	}
	for (int i=2; i<n; i++) {
		if (sieve[i]) {
			cout << i << " ";
		}
	}
	return 0;
}
