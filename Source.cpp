#include <windows.h>
#include <iostream>
#include <stack>
using namespace std;

struct Queue {
    char* data;
    int in;
    int out;
    int capacity;
};

void create(Queue& q, int capacity)
{
    q.data = new char[capacity];
    q.in = -1;
    q.out = -1;
    q.capacity = capacity;
}

void enqueue(Queue& q, char x) {
    if (q.in + 1 >= q.capacity) {
        cout << " queue is full " << endl;
        return;
    }

    q.data[++q.in] = x;
}


char dequeue(Queue& q) {
    if (q.out == q.in) {
        cout << "queue is empty" << endl;
        return '\0';
    }

    return q.data[++q.out];
}


bool isEmpty(Queue& q) {
    if (q.in == -1) {
        return true;
    }
    return false;
}

void empty(Queue& q) {
    q.in = -1;
    q.out = -1;
}

int sizeOfQueue(Queue& q) {
    return q.in + 1;
}

Queue ExtractTerms(const char* strIn)
{
    Queue queue;
    create(queue, strlen(strIn));

    for (int i = 0; i < strlen(strIn); i++)
    {
        if (isblank(strIn[i]))
            continue;

        if (isdigit(strIn[i]))
        {
            int j = 0;
            while (isdigit(strIn[i + j]))
                j++;

            char* numstr = new char[j + 1];
            for (int z = 0; z < j; z++)
                numstr[z] = strIn[i + z];
            numstr[j] = '\0';

            enqueue(queue, (char)atoi(numstr));

            i += j-1;
            delete[]numstr;
        }
        else
            enqueue(queue, strIn[i]);
    }

    return queue;
}

Queue Trans2Postfix(Queue qIn)
{
    Queue q;
    create(q, qIn.capacity);

    stack <char> s;

    // length of expression
    int length = sizeOfQueue(qIn);

    char curchar;

    // reading from right to left
    for (int i = 0; i < length; i++)
    {
        curchar = qIn.data[i];
        // check if symbol is operator
        if (curchar == '(' || curchar == '+' || curchar == '-' || curchar == '*' || curchar == '/')
        {
            s.push(curchar);
        }
        else if (curchar == ')')
        {
            while (s.top() != '(')
            {
                enqueue(q, s.top());
                s.pop();
            }
            s.pop();
        }
        else
        {
            enqueue(q, curchar);

            if (!s.empty() && (s.top() == '*' || s.top() == '/'))
            {
                enqueue(q, s.top());
                s.pop();
            }
        }
    }

    while (!s.empty())
    {
        enqueue(q, s.top());
        s.pop();
    }

    // stack contains only the Postfix expression
    return q;
}



int main(int argc, char** argv)
{
    char strIn[] = "25 * 46 / (56 + 34 + 56*95)" ;
   
    Queue queue = ExtractTerms(strIn);

    char curchar;

    cout << "Infix: ";

    for (int i = 0; i < sizeOfQueue(queue); i++)
    {
        curchar = queue.data[queue.out + 1];
        if (curchar == '+' || curchar == '-' || curchar == '*' || curchar == '/' || curchar == ')' || curchar == '(')
            cout << (char)dequeue(queue) << " ";
        else
            cout << (int)dequeue(queue) << " ";
    }

    cout << "\nPostfix:";

    Queue postQueue = Trans2Postfix(queue);

    for (int i = 0; i < sizeOfQueue(postQueue); i++)
    {
        curchar = postQueue.data[postQueue.out + 1];
        if (curchar == '+' || curchar == '-' || curchar == '*' || curchar == '/')
            cout << (char)dequeue(postQueue) << " ";
        else
            cout << (int)dequeue(postQueue) << " ";
    }


    return 0;
}