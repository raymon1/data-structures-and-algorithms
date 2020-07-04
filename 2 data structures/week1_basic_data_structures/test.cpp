#include <iostream>
#include <stack>
#include <string>


struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    void deleteNode(ListNode *&node) {  
        std::cout<< node << " " << node->next << "\n";        
        node = node->next;
        std::cout<< node << " " << node->next << "\n";
    }
};

int main() {
    ListNode x1 = ListNode(1);
    ListNode x2 = ListNode(2);
    ListNode x3 = ListNode(3);
    ListNode x4 = ListNode(4);
    x1.next = &x2;
    x2.next = &x3;
    x3.next = &x4;

    Solution sol;
    sol.deleteNode(x1.next);
    std::cout << x1.next << " " << x1.next->next << "\n" 
        << x1.val << " " << x1.next->val << " " << x1.next->next->val << "\n";

    return 0;
}
