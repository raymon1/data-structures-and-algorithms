#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


class Hash {
	unsigned long long m;
	vector<unsigned long long> h;
	vector<unsigned long long> xPower;

public:
	Hash() {}

	Hash(string& s, unsigned long long m, unsigned long long x) {
		this->m = m;
		h.resize(s.size() + 1);
		xPower.resize(s.size() + 1);

		h[0] = 0;
		for (size_t i = 1; i < h.size(); ++i) {
			h[i] = ((x * h[i-1] + s[i - 1]) % m + m) % m;
		}

		xPower[0] = 1;
		for (size_t i = 1; i < xPower.size(); ++i) {
			xPower[i] = (x * xPower[i - 1] % m + m) % m;
		}
	}	
	
	unsigned long long BigH(int i, int l, unsigned long long x) {		
		return (h[i + l] - xPower[l] * h[i] % m + m) % m;
	}
};

class Solver
{
	string s;
	unsigned long long x;
	Hash h1, h2;

public:
	Solver(string s) {
		s = s;
		unsigned long long m1 = 1000000003;
		unsigned long long m2 = 1000000007;
		x = rand() % 1000000000 + 1;

		h1 = * new Hash(s, m1, x);
		h2 = * new Hash(s, m2, x);
	}

	bool ask(int a, int b, int l) {
		return h1.BigH(a, l, x) == h1.BigH(b, l, x)
			&& h2.BigH(a, l, x) == h2.BigH(b, l, x);
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
