#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool AllSubtreeIsMinMax(const vector<Node>& tree, int i, int min, int max) {
  if (i == -1)
    return true;

  Node n = tree[i];
  int leftMin = min;
  int leftMax = n.key;
  int rightMin = n.key;
  int rightMax = max;

  if (n.key > min && n.key < max && AllSubtreeIsMinMax(tree, n.left, leftMin, leftMax) && AllSubtreeIsMinMax(tree, n.right, rightMin, rightMax)){
    return true;
  }

  return false;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  if (tree.size() == 0 || AllSubtreeIsMinMax(tree, 0, std::numeric_limits<int>::min(), std::numeric_limits<int>::max()))
    return true;
  return false;
}

int main() {
  int nodes;
  cin >> nodes;
  vector<Node> tree;
  for (int i = 0; i < nodes; ++i) {
    int key, left, right;
    cin >> key >> left >> right;
    tree.push_back(Node(key, left, right));
  }
  if (IsBinarySearchTree(tree)) {
    cout << "CORRECT" << endl;
  } else {
    cout << "INCORRECT" << endl;
  }
  return 0;
}
