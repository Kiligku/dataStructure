#pragma once
#include <iostream>
#include "stack.hpp"
using namespace std;
template <class T>
class Queue
{
private:
    Stack<T> s1;
    Stack<T> s2;

public:
    Queue()
    {
    }

    int QueueEmpty()
    {
        return s1.StackEmtpy();
    }

    int GetHead(T &ele)
    {
        if (QueueEmpty())
        {
            return 0;
        }
        else
        {
            s1.GetTop(ele);
            return 1;
        }
    }

    int EnQueue(T ele)
    {
        if (this->QueueLength() >= MAXSIZE)
        {
            return 0;
        }
        else
        {
            while (!s1.StackEmtpy())
            {
                T e;
                s1.Pop(e);
                s2.Push(e);
            }
            s1.Push(ele);
            while (!s2.StackEmtpy())
            {
                T e;
                s2.Pop(e);
                s1.Push(e);
            }
            return 1;
        }
    }

    int DeQueue(T &ele)
    {
        if (s1.StackEmtpy())
        {
            return 0;
        }
        else
        {
            s1.Pop(ele);
            return 1;
        }
    }

    int QueueLength()
    {
        return this->s1.len;
    }

    void QueueToArray(T *seq)
    {
    }
};