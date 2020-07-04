#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters =    4;
int const NA      =   -1;

struct Node
{
	int next [Letters];

	Node ()
	{
		fill (next, next + Letters, NA);
	}

	bool isLeaf () const
	{
	    return (next[0] == NA && next[1] == NA && next[2] == NA && next[3] == NA);
	}
};

int letterToIndex (char letter)
{
	switch (letter)
	{
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert (false); return -1;
	}
}

vector <int> solve (const string& text, int n, const vector <string>& patterns)
{
	vector <int> result;

	vector <Node> t;
	t.push_back(Node());

	for(auto pattern : patterns) {
		int currentNode = 0;
		for(auto symb : pattern) {
			if(t[currentNode].next[letterToIndex(symb)] != -1) {
				currentNode = t[currentNode].next[letterToIndex(symb)];
			}
			else {
				t[currentNode].next[letterToIndex(symb)] = t.size();
				currentNode = t.size();
				t.push_back(Node());
			}
		}
	}

	for (int i = 0; i < text.size(); ++i){
		int currentNode = 0;
		for (int j = i; j < text.size(); ++j){
			if(t[currentNode].next[letterToIndex(text[j])] != -1) {
				currentNode = t[currentNode].next[letterToIndex(text[j])];
				if(t[currentNode].isLeaf()) {
					result.push_back(i);
					break;
				}
			}
			else {
				break;
			}
		}
	}

	return result;
}

int main (void)
{
	string t;
	cin >> t;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++)
	{
		cin >> patterns[i];
	}

	vector <int> ans;
	ans = solve (t, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++)
	{
		cout << ans[i];
		if (i + 1 < (int) ans.size ())
		{
			cout << " ";
		}
		else
		{
			cout << endl;
		}
	}

	return 0;
}
