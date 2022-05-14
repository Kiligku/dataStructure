#include <iostream>
#include "stack.hpp"
#include "queue.hpp"
using namespace std;

void StackTest01()
{
    Stack<int> s;
    for (int i = 0; i < 5; i++)
    {
        s.Push(i);
    }
    while (!s.StackEmtpy())
    {
        int temp;
        s.Pop(temp);
    }
}

void QueueTest01()
{
    Queue<int> q;
    for (int i = 0; i < 50; i++)
    {
        q.EnQueue(i);
    }
    while (!q.QueueEmpty())
    {
        int ele;
        q.DeQueue(ele);
        cout << ele << endl;
    }
    int qTop;
    cout << q.GetHead(qTop) << endl;
}

int main()
{
    QueueTest01();
    return 0;
}