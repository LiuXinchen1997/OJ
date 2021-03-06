/*
 * @lc app=leetcode.cn id=109 lang=cpp
 *
 * [109] 有序链表转换二叉搜索树
 */

// @lc code=start
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
private:
    ListNode* head;

public:
    TreeNode* buildTree(int l, int r) {
        if (l > r) { return NULL; }

        int mid = (l+r) / 2;
        TreeNode* left = buildTree(l, mid-1);

        TreeNode* root = new TreeNode(this->head->val);
        root->left = left;
        this->head = this->head->next;

        root->right = buildTree(mid+1, r);
        return root;
    }

    TreeNode* sortedListToBST(ListNode* head) {
        if (!head) { return NULL; }

        int size = 0;
        ListNode* cur = head;
        while (cur) {
            size += 1;
            cur = cur->next;
        }

        this->head = head;
        TreeNode* root = buildTree(0, size-1);
        return root;
    }
};
// @lc code=end

