#include <algorithm>
#include <iostream>
#include <vector>
#include <stack>
#if defined(__unix__) || defined(__APPLE__)
#include <sys/resource.h>
#endif

class Node;

class Node {
public:
    int key;
    Node *parent;
    std::vector<Node *> children;

    Node() {
      this->parent = NULL;
    }

    void setParent(Node *theParent) {
      parent = theParent;
      parent->children.push_back(this);
    }
};


int main_with_large_stack_space() {
  std::ios_base::sync_with_stdio(0);
  int n;
  std::cin >> n;

  std::vector<Node> nodes;
  nodes.resize(n);
  int rootIndex;
  for (int child_index = 0; child_index < n; child_index++)
  {
    int parent_index;
    std::cin >> parent_index;
    if (parent_index >= 0)
      nodes[child_index].setParent(&nodes[parent_index]);
    else {
      rootIndex = child_index;
    }
    nodes[child_index].key = child_index;
  }

  // Replace this code with a faster implementation
  std::stack<int> dfs;
  std::vector<int> maxHeights(n, 0);
  dfs.push(rootIndex);
  maxHeights[rootIndex] = 1;
  int maxHeight = 0;
  while (!dfs.empty())
  {
    int index = dfs.top();
    dfs.pop();

    if(maxHeights[index] == 0) {
      maxHeights[index] = maxHeights[nodes[index].parent->key] + 1;
      if(maxHeights[index] > maxHeight)
        maxHeight = maxHeights[index];
    }

    for (int i = 0; i < nodes[index].children.size(); ++i)
    {
      dfs.push(nodes[index].children[i]->key);
    }
  }
    
  std::cout << maxHeight << std::endl;
  return 0;
}

int main (int argc, char **argv)
{
#if defined(__unix__) || defined(__APPLE__)
  // Allow larger stack space
  const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
  struct rlimit rl;
  int result;

  result = getrlimit(RLIMIT_STACK, &rl);
  if (result == 0)
  {
      if (rl.rlim_cur < kStackSize)
      {
          rl.rlim_cur = kStackSize;
          result = setrlimit(RLIMIT_STACK, &rl);
          if (result != 0)
          {
              std::cerr << "setrlimit returned result = " << result << std::endl;
          }
      }
  }

#endif
  return main_with_large_stack_space();
}
