#include <iostream>
#include <vector>
#include <cassert>

using std::cin;
using std::cout;
using std::vector;
using std::max;

class StackWithMax {
    vector<int> stack;
    vector<int> maxStack;

  public:

    void Push(int value) {
        stack.push_back(value);
        int max = maxStack.empty() ? 0 : maxStack.back();
        maxStack.push_back(std::max(value, max));
    }

    void Pop() {
        assert(stack.size());
        stack.pop_back();
        maxStack.pop_back();
    }

    int Top() {
        return stack.back();
    }

    int Max() {
        assert(maxStack.size());
        return maxStack.back();
    }

    int size() {
        return stack.size();
    }
};

class queue {
    StackWithMax s1, s2;
  
  public:

    void Push(int value) {
        s1.Push(value);
    }

    void Pop() {
        assert(s1.size() + s2.size());

        if(s2.size() == 0) {
            while(s1.size() > 0){
                s2.Push(s1.Top());
                s1.Pop();
            }
        }

        s2.Pop();
    }

    int Max() {
        assert(s1.size() + s2.size());

        return max(s1.size() > 0 ? s1.Max() : 0, s2.size() > 0 ? s2.Max() : 0);
    }
};

void
max_sliding_window_naive(vector<int> const &A, int w)
{
    for (size_t i = 0; i < A.size() - w + 1; ++i) {
        int window_max = A.at(i);
        for (size_t j = i + 1; j < i + w; ++j)
            window_max = max(window_max, A.at(j));

        cout << window_max << " ";
    }

    return;
}

void max_sliding_window(vector<int> const & A, int w) {
    queue window;
    for (size_t i = 0; i < w - 1; ++i)
    {
        window.Push(A[i]);
    }

    for (size_t i = w - 1; i < A.size(); ++i) {
        window.Push(A[i]);

        cout << window.Max() << " ";

        window.Pop();
    }

    return;
}

int main() {
    int n = 0;
    cin >> n;

    vector<int> A(n);
    for (size_t i = 0; i < n; ++i)
        cin >> A.at(i);

    int w = 0;
    cin >> w;

    max_sliding_window(A, w);

    return 0;
}
