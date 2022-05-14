#pragma once
using namespace std;
#define MAXSIZE 10
template <class T>
class Stack
{
private:
    T data[MAXSIZE];
    int top;

public:
    int len;
    Stack()
    {
        this->len = 0;
        this->top = -1;
    }

    int Push(T ele)
    {
        if (this->len >= MAXSIZE)
        {
            return 0;
        }
        else
        {
            this->data[++top] = ele;
            this->len++;
            return 1;
        }
    }

    int Pop(T &ele)
    {
        if (top == -1)
        {
            return 0;
        }
        else
        {
            T topEle = this->data[top--];
            ele = topEle;
            this->len--;
            return 1;
        }
    }

    int GetTop(T &ele)
    {
        if (top == -1)
        {
            return 0;
        }
        else
        {
            ele = this->data[this->top];
            return 1;
        }
    }

    void StackToArray(T *Seq)
    {
    }

    int StackEmtpy()
    {
        return this->top == -1;
    }
};
