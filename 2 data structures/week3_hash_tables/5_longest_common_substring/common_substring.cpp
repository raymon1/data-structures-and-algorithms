#include <iostream>
#include <cmath>
#include <vector>
#include <unordered_set>

using namespace std;

struct Answer {
	size_t i, j, len;
};

class Hash {
	unsigned long long m;
	vector<unsigned long long> h;
	vector<unsigned long long> xPower;

public:
	Hash() {}

	Hash(const string& s, unsigned long long m, unsigned long long x) {
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
	
	unsigned long long BigH(int i, int l) {		
		return (h[i + l] - xPower[l] * h[i] % m + m) % m;
	}
};


Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	unsigned long long m1 = 1000000003;
	unsigned long long m2 = 1000000007;
	unsigned long long x = rand() % 1000000000 + 1;

	Hash hs1(s, m1, x);
	Hash hs2(s, m2, x);
	
	Hash ht1(t, m1, x);
	Hash ht2(t, m2, x);

	size_t lo = 0;
	size_t hi = min(s.size(), t.size());
	size_t l = 0;

	while (lo <= hi) {
		l = lo + (hi - lo) / 2;

		unordered_set<unsigned long long> sHashes1;
		unordered_set<unsigned long long> sHashes2;
		for (size_t i = 0; i <= s.size() - l; i++)
		{
			sHashes1.insert(hs1.BigH(i, l));
			sHashes2.insert(hs2.BigH(i, l));
		}
		bool found = false;
		for (size_t j = 0; j <= t.size() - l; j++)
		{
			unsigned long long tHash1 = ht1.BigH(j, l);
			unsigned long long tHash2 = ht2.BigH(j, l);
			if (sHashes1.find(tHash1) != sHashes1.end() && sHashes2.find(tHash2) != sHashes2.end())
			{
				for (size_t i = 0; i <= s.size() - l; i++)
				{
					if(tHash1 == hs1.BigH(i, l) && tHash2 == hs2.BigH(i, l)) {
						ans = {i, j, l};
						break;
					}
				}
				found = true;
				break;
			}
		}

		if (found) {
			lo = l + 1;
		}
		else {
			hi = l - 1;
		}
	}

	return ans;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
