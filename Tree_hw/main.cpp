#include <iostream>
#include "string.h"
#include "myTree.h"
#include "queue"
using namespace std;

TreeNode *createTreeNode(int data)
{
    if (data == -1)
    {
        return NULL;
    }
    else
    {
        TreeNode *T = new TreeNode();
        T->data = data;
        return T;
    }
}

/** TODO: 根据层次遍历序列创建二叉树 */
MyTree createTreeWithLevelOrder(int *data, int size)
{
    MyTree newTree;
    queue<TreeNode *> NodeQueue;
    TreeNode *r = createTreeNode(data[0]);
    NodeQueue.push(r);
    TreeNode *curr = r;
    int i = 0;
    while (i < size)
    {
        if (i == size - 1)
            break;
        TreeNode *Tl = createTreeNode(data[++i]);
        NodeQueue.push(Tl); // 左子树入队
        TreeNode *Tr = createTreeNode(data[++i]);
        NodeQueue.push(Tr); // 右子树入队
        if (curr)
        {
            curr->lchild = Tl;
            curr->rchild = Tr;
        }
        NodeQueue.pop();          // 已经添加完左右子树的树出队
        curr = NodeQueue.front(); // 改变即将添加左右子树的树
    }
    newTree.root = r;
    return newTree;
}


void getDigits(char *buff, int *data)
{
    int len = strlen(buff);
    int index = 0;
    for (int i = 0; i < len; i++)
    {
        int num = 0;
        if (buff[i] == '#')
        {
            num = -1;
            i++;
        }
        else
        {
            while (buff[i] != ' ' && buff[i] != '\0')
            {
                num = num * 10 + (buff[i++] - '0');
            }
        }
        data[index++] = num;
    }
}

int main()
{
    int SIZE = 128;
    int MAX_NUM = 10;
    char buff[SIZE];
    char num[MAX_NUM];

    FILE *fp = fopen("./test.txt", "r");
    if (!fp)
    {
        perror("打开文件时发生错误");
        return -1;
    }
    else
    {
        int cnt = 0;
        while (fgets(num, MAX_NUM, fp) && fgets(buff, SIZE, fp))
        {
            char *nextline = strchr(buff, '\n'); //查找换行符
            if (nextline)                        //如果find不为空指针
                *nextline = '\0';                //就把一个空字符放在这里
            nextline = strchr(buff, '\r');       //查找回车符
            if (nextline)                        //如果find不为空指针
                *nextline = '\0';                //就把一个空字符放在这里
            printf("Case %d, data: %s, nodes number: %s", cnt, buff, num);
            int size = atoi(num);
            int data[size];
            cnt++;
            getDigits(buff, data);
            /** 任务一 */
            MyTree tree = createTreeWithLevelOrder(data, size);
            cout << "Answer for task 1 is: " << endl;
            cout << "preOrderTraverse is: ";
            tree.preOrderTraverse();
            cout << endl;
            cout << "inOrderTraverse is: ";
            tree.inOrderTraverse();
            cout << endl;
            cout << "postOrderTraverse is: ";
            tree.postOrderTraverse();
            cout << endl;
            /** 任务二 */
            int max_path_sum = tree.maxPathSum();
            cout << "Answer for task 2 is " << max_path_sum << endl;
            /** 任务三 */
            int weight_sum = tree.sumOfLeftLeaves();
            cout << "Answer for task 3 is " << weight_sum << endl;
            /** 任务四 */
            MyTree invTree = tree.invertTree();
            cout << "inOrderTraverse for task 4 is:";
            invTree.inOrderTraverse();
            cout << endl
                 << endl;
            tree.DeleteTree(tree.root);
        }
        return 0;
    }
}
