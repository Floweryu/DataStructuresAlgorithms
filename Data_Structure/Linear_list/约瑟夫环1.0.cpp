#include <iostream>

using namespace std;

typedef struct list
{
    int num;
    struct list *next;
}LinkList;



int main()
{
    LinkList *head, *p, *q;
    int m, r;
    cin>>m>>r;
    if (m == 0 || r == 0);
    else
    {
        head = new LinkList;
        head->next = head;
        p = head;
        p->num = 1;

        p->next = NULL;
        q = p;

        for (int i = 2; i <= m; i++)
        {
            p = new LinkList;
            p->num = i;

            p->next = NULL;
            q->next = p;
            q = p;
        }
        q->next = head;

        p = head;
        while (p->next != p)
        {
            int i = 1;
            while (i < r-1)
            {
                p = p->next;
                i++;
            }
            q = p->next;
            p->next = q->next;
            cout<<q->num<<" ";
            delete q;
            p = p->next;
        }
        cout<<p->num<<endl;
    }
}
