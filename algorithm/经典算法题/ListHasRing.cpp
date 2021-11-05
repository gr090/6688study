#include<iostream>
using namespace std;
 
typedef struct node
{
    int data;  
    struct node *next;
}Node;
 
Node *createList(int n)
{
    Node *p = new Node[n];
    for( int i = 1; i < n; ++i)
    {
        p[i - 1].next = &p[i];
        p[i - 1].data = i;
    }
    p[n - 1].next = NULL;
    p[n - 1].data = n;
    return p;
}
 
Node *createListWithRing(int n)
{
    Node *p = new Node[n];
    for( int i = 1; i < n; ++i)
    {
        p[i - 1].next = &p[i];
        p[i - 1].data = i;
    }
    p[n - 1].next = &p[n/2];
    p[n - 1].data = n;
    return p;
}
 
//pFast相当于兔子，pSlow相当于乌龟
bool listHasRing(Node *p)
{
    Node *pSlow = &p[0];
    Node *pFast = &p[1];
    while(NULL != pSlow && NULL != pFast -> next) 
    {
        if(pSlow == pFast)
    {
      return true;
    }

        pSlow = pSlow -> next;
        pFast = pFast -> next ->next;
    }
  
    return false;
}

 
int main()
{
    Node *head = createList(10);
    cout << listHasRing(head) << endl;
    delete [] head; 
 
    head = createListWithRing(10);
    cout << listHasRing(head) << endl;
    delete [] head; 
    return 0;
}