#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

bool areEqual(const string& s, const string& t, const int i){
    for (size_t j = 0; j < s.size(); ++j){
        if(t[i+j] != s[j]){
            return false;
        }
    }
    return true;
}

unsigned long long polyHash(const string& s, const int p, const int x) {
    unsigned long long hash = 0;
    for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
        hash = (hash * x + s[i]) % p;
    return hash;
}

std::vector<unsigned long long> precomputeHashes(const string& t, const int len, const unsigned long long p, const unsigned long long x) {
    std::vector<unsigned long long> H(t.size() - len + 1);

    H[t.size() - len] = polyHash(t.substr(t.size() - len), p, x);

    unsigned long long y = 1;
    for (int i = 0; i < len; ++i){
        y = (y * x) % p;
    }

    for (int i = t.size() - len - 1; i >= 0; --i){
        H[i] = (H[i + 1] * x % p + t[i] - y * t[i + len] % p + p) % p;
    }

    return H;
}

std::vector<int> get_occurrences(const Data& input) {
    int p = 1000000007;
    int x = std::rand() % (p - 1) + 1;
    const string &s = input.pattern, t = input.text;
    int sSize = s.size();

    unsigned long long pHash = polyHash(s, p, x);
    std::vector<unsigned long long> H = precomputeHashes(t, sSize, p, x);

    std::vector<int> ans;
    for (size_t i = 0; i + sSize <= t.size(); ++i) {
        if (H[i] == pHash && areEqual(s, t, i))
        {        
            ans.push_back(i);
        }
    }

    return ans;
}



int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
