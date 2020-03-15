#include <stdio.h>
#include <stdlib.h>

typedef struct _Address
{
    int pre;
    int data;
    int next;
    struct _Address *pnext;
} Address, *PAddress;

void Attach(int pre, int data, int next, PAddress *pRear)
{
    PAddress P;
    P = (PAddress)malloc(sizeof(Address));
    P->pre = pre;
    P->data = data;
    P->next = next;
    P->pnext = NULL;
    (*pRear)->pnext = P;
    (*pRear) = P;
}

void reverse_good(PAddress P, int K, int N) //递归做法(带头结点)
{
    PAddress head, rear, temp;
    int cnt = 1;
    head = P->pnext;
    rear = head->pnext;
    while (cnt < K)
    {
        temp = rear->pnext;
        rear->pnext = head;
        rear->next = head->pre;
        head = rear;
        rear = temp;
        cnt++;
    }
    P->pnext->pnext = rear;
    if (rear)
        P->pnext->next = rear->pre;
    else
        P->pnext->next = -1;
    temp = P->pnext;
    P->pnext = head;
    P->next = head->pre;
    N = N - K;
    if (N >= K)
    {
        reverse_good(temp, K, N);
    }
}

PAddress ReadAddress()
{
    int first, N, K, pre, data, next;
    PAddress P, P2, head, rear, temp;
    P = (PAddress)malloc(sizeof(Address));
    P->pnext = NULL;
    head = rear = P;

    scanf("%d %d %d", &first, &N, &K);
    while (N--)
    {
        scanf("%d %d %d", &pre, &data, &next);
        Attach(pre, data, next, &rear);
    }
    P2 = (PAddress)malloc(sizeof(Address));
    P2->next = first;
    P2->pnext = NULL;
    rear = P2;
    temp = P->pnext;

    N = 0;
    while (temp)
    {
        if (rear->next == temp->pre)
        {
            head->pnext = temp->pnext;
            rear->pnext = temp;
            temp->pnext = NULL;
            rear = temp;
            head = P;
            temp = P->pnext;
            N++;
            continue;
        }
        head = temp;
        temp = head->pnext;
    }

    //开始翻转
    if (N >= K)
    {
        reverse_good(P2, K, N);
    }

    temp = P2;
    P2 = P2->pnext;
    free(temp);
    return P2;
}

void PrintAddress(PAddress P)
{
    while ((P->next) != -1)
    {
        printf("%05d %d %05d", P->pre, P->data, P->next);
        printf("\n");
        P = P->pnext;
    }
    printf("%05d %d %d", P->pre, P->data, P->next);
}

int main()
{
    PAddress P;
    P = ReadAddress();
    PrintAddress(P);

    return 0;
}
