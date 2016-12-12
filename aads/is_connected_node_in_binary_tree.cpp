#include <vector>
#include <utility>
#include <unordered_map>
#include <unordered_set>
#include <cassert>

using namespace std;

struct TreeNode {
    char val;
    TreeNode *left, *right;
    TreeNode(char val):val(val), left(nullptr), right(nullptr) {}
};

static void traverse(TreeNode *root, unordered_map<char, unordered_set<char>> &dict_to_childs) {
    if (root) {
        unordered_set<char> unset;
        if (root->left)
            unset.insert(root->left->val);
        
        if (root->right)
            unset.insert(root->right->val);
        
        dict_to_childs.insert(make_pair(root->val, unset));
        
        traverse(root->left, dict_to_childs);
        traverse(root->right, dict_to_childs);
    }
}

/* Input：输入为一颗二叉树，每个节点的值为一个字符，且所有节点的值都不相同；
 * 还有一个数组(vector)，代表一些节点，判断这些节点在二叉树上是否是连通的。
 * 
 * Output：true; false。
 * 
 */
static bool is_connected(TreeNode *root, vector<char> vi) {
    unordered_map<char, bool> tb;
    unordered_map<char, unordered_set<char>> dict_to_childs;
    
    for (auto ch : vi) {
        tb.insert(make_pair(ch, true));
    }
    
    traverse(root, dict_to_childs);

    for (auto ch : vi) {
        for (auto child : dict_to_childs[ch]) {
            if (tb.count(child)) {
                tb[child] = false;
            }
        }
    }
    
    int cnt = 0;
    for (auto &item : tb) {
        if (item.second)
            cnt++;
        if (cnt > 1)
            return false;
    }
    
    return true;
}

void test_is_connected() {
    TreeNode *root = new TreeNode('a');
    root->left = new TreeNode('b');
    root->right = new TreeNode('c');
    
    TreeNode *pb = root->left;
    pb->left = new TreeNode('d');
    pb->right = new TreeNode('e');
    
    TreeNode *pc = root->right;
    pc->right = new TreeNode('h');
    
    TreeNode *pe = pb->right;
    pe->left = new TreeNode('f');
    pe->right = new TreeNode('g');
    
    TreeNode *ph = pc->right;
    ph->left = new TreeNode('i');
    ph->right = new TreeNode('j');
    
    assert(is_connected(root, {'h', 'i', 'j'}) == true);
    assert(is_connected(root, {'i', 'j'}) == false);
    assert(is_connected(root, {'e', 'b', 'c', 'a'}) == true);
}
