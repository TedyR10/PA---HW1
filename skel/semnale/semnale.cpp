#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int mod = 1000000007;

// Calculates (x^y)%p
unsigned long long power(unsigned long long x,
                                  int y, int p) {
    unsigned long long res = 1;

	// Update x if it is more than or
	// equal to p
    x = x % p;

    while (y > 0) {
        // If y is odd, multiply x with result
        if (y & 1)
            res = (res * x) % p;

        // y must be even now
        y = y >> 1;
        x = (x * x) % p;
    }
    return res;
}

// Returns n^(-1) mod p
unsigned long long modInverse(unsigned long long n,
                                            int p) {
    return power(n, p - 2, p);
}

// Returns nCr % p using Fermat's little
// theorem.
unsigned long long nCrModPFermat(unsigned long long n,
                                 int r, int p) {
    // If n<r, then nCr should return 0
    if (n < r)
        return 0;
    // Base case
    if (r == 0)
        return 1;

    // Fill factorial array so that we
    // can find all factorial of r, n
    // and n-r
    unsigned long long fac[n + 1];
    fac[0] = 1;
    for (int i = 1; i <= n; i++)
        fac[i] = (fac[i - 1] * i) % p;

    return (fac[n] * modInverse(fac[r], p) % p
            * modInverse(fac[n - r], p) % p)
           % p;
}

int type1(int x, int y) {
    return nCrModPFermat(x + 1, y, mod);
}

int type2(int x, int y) {
	long long sum = 0;
    for (int i = ceil(y / 2); i <= y; i++) {
		sum = (sum + nCrModPFermat(x + 1, i, mod) *
		nCrModPFermat(i, y - i, mod) % mod) % mod;
	}

	return sum;
}

int main() {
    freopen("semnale.in", "r", stdin);
	freopen("semnale.out", "w", stdout);

	int sig_type, x, y;

	cin >> sig_type >> x >> y;

    switch (sig_type) {
		case 1:
			cout << type1(x, y);;
			break;
		case 2:
			cout << type2(x, y);
			break;
		default:
			cout << "wrong task number" << endl;
	}

    return 0;
}
