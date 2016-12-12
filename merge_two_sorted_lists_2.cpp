
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int val):val(val), next(nullptr) {}
};

static ListNode *reverse_list(ListNode *head) {
    ListNode *prev = nullptr;

    while (head) {
        ListNode *post = head->next;
        head->next = prev;
        prev = head;
        head = post;
    }

    return prev;
}

/* Input: 2个升序排列的单向链表；
 * 
 * Output: 将两个链表合并，并返回降序排序的链表。
 * 挑战：尽量少的分配内存。
 */
static ListNode *merge_two_lists(ListNode *l1, ListNode *l2) {
    ListNode *l3 = nullptr;
    ListNode *last = nullptr;

    while (l1 && l2) {
        ListNode *cur;
        if (l1->val < l2->val) {
            cur = l1;
            l1 = l1->next;
        } else {
            cur = l2;
            l2 = l2->next;
        }

        if (!l3) {
            l3 = cur;
            cur->next = nullptr;
            last = l3;
        } else {
            last->next = cur;
            cur->next = nullptr;
            last = last->next;
        }
    }

    ListNode *p = l1 ? l1 : l2;
    if (!l3) {
        l3 = p;
    } else {
        last->next = p;
    }

    return l3;
}

static ListNode *merge_two_ascend_lists_to_descend_list(ListNode *l1, ListNode *l2) {
    return reverse_list(merge_two_lists(l1, l2));
}

void test_merge_two_ascend_lists_to_descend_list() {
    ListNode *L1 = new ListNode(1);
    L1->next = new ListNode(3);
    L1->next->next = new ListNode(5);
    
    ListNode *L2 = new ListNode(2);
    L2->next = new ListNode(4);
    L2->next->next = new ListNode(6);
    
    ListNode *L3 = merge_two_ascend_lists_to_descend_list(L1, L2);
    
    
    int i = 6;
    for (ListNode *p = L3; p != nullptr; p = p->next, i--) {
//        cout << p->val << endl;
        assert(i == p->val);
    }
}
