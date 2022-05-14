#pragma once
using namespace std;
class TreeNode
{
public:
    int data;
    TreeNode *lchild;
    TreeNode *rchild;
    TreeNode();
};

class MyTree
{
public:
    TreeNode *root;
    MyTree();
    /** TODO:  任务一：请你通过队列来实现层次遍历构建二叉树，并返回二叉树的头结点 */

    void preOrderTraverse(TreeNode *root);
    void preOrderTraverse();
    void inOrderTraverse(TreeNode *root);
    void inOrderTraverse();
    void postOrderTraverse(TreeNode *root);
    void postOrderTraverse();

    /** TODO: 任务二：请你通过深度优先遍历来求取该二叉树的最大路径和 */
    int maxPathSum(TreeNode *T);
    int maxPathSum();
    /** ToDO: 任务三：请你通过递归求取该二叉树的所有左子叶权重之和 */
    int sumOfLeftLeaves(TreeNode *T);
    int sumOfLeftLeaves();

    /** TODO: 任务四：请你通过递归求取该树的镜像，即翻转该二叉树 */
    TreeNode* invertTree(TreeNode *T);
    MyTree invertTree();

    void DeleteTree(TreeNode *T);
};