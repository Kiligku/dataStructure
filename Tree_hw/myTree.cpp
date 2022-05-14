#include "myTree.h"
#include <iostream>
using namespace std;
TreeNode::TreeNode()
{
    this->data = 0;
    this->lchild = NULL;
    this->rchild = NULL;
}

MyTree::MyTree()
{
    this->root = NULL;
}

/** TODO: 任务一：用三种顺序遍历树 */
void MyTree::preOrderTraverse(TreeNode *T)
{
    if (T)
    {
        cout << T->data << " ";
        preOrderTraverse(T->lchild);
        preOrderTraverse(T->rchild);
    }
}

void MyTree::preOrderTraverse()
{
    preOrderTraverse(this->root);
}

void MyTree::inOrderTraverse(TreeNode *T)
{
    if (T)
    {
        inOrderTraverse(T->lchild);
        cout << T->data << " ";
        inOrderTraverse(T->rchild);
    }
}

void MyTree::inOrderTraverse()
{
    inOrderTraverse(this->root);
}

void MyTree::postOrderTraverse(TreeNode *T)
{
    if (T)
    {
        postOrderTraverse(T->lchild);
        postOrderTraverse(T->rchild);
        cout << T->data << " ";
    }
}

void MyTree::postOrderTraverse()
{
    postOrderTraverse(this->root);
}

/** TODO: 任务二：请你通过深度优先遍历来求取该二叉树的最大路径和 */
int MyTree::maxPathSum(TreeNode *T)
{
    if (!T)
        return 0;
    int leftSum = maxPathSum(T->lchild);
    int rightSum = maxPathSum(T->rchild);
    return max(leftSum, rightSum) + T->data;
}

int MyTree::maxPathSum()
{
    return maxPathSum(this->root);
}

/** TODO: 任务三：请你通过递归求取该二叉树的所有左子叶权重之和 */
int MyTree::sumOfLeftLeaves(TreeNode *T)
{
    if (!T)
        return 0;
    int leftSum = sumOfLeftLeaves(T->lchild);
    int rightSum = sumOfLeftLeaves(T->rchild);
    if (T->lchild && !T->lchild->lchild && !T->lchild->rchild)
        return T->lchild->data + rightSum;
    return leftSum + rightSum;
}

int MyTree::sumOfLeftLeaves()
{
    return sumOfLeftLeaves(this->root);
}
/** TODO: 任务四：请你通过递归求取该树的镜像，即翻转该二叉树 */
TreeNode *MyTree::invertTree(TreeNode *T)
{
    if (!T)
        return T;
    TreeNode *tmp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = tmp;
    invertTree(T->lchild);
    invertTree(T->rchild);
    return T;
}

// 删除树
MyTree MyTree::invertTree()
{
    MyTree invTree;
    invTree.root = invertTree(this->root);
    return invTree;
}


void MyTree::DeleteTree(TreeNode *T)
{
    if (!T)
    {
        return;
    }
    DeleteTree(T->lchild);
    DeleteTree(T->rchild);
    delete T;
    return;
}