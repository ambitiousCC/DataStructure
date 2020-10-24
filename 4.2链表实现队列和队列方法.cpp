#include <iostream>
#define QElemType char
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1


using namespace std;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
}QNode, *QueuePtr;
typedef struct
{
    QueuePtr front;
    QueuePtr rear;
}LinkQueue;

//初始化
Status InitQueue(LinkQueue &Q)
{
    Q.front=Q.rear=new QNode;
    Q.front->next=NULL;
    return OK;
}

//入队
Status EnQueue(LinkQueue &Q,QElemType e)
{
    QNode *p = new QNode;
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
    return OK;
}

//出队
Status DeQueue(LinkQueue &Q,QElemType &e)
{
    if(Q.front==Q.rear) return ERROR;
    QNode *p=Q.front->next;
    e=p->data;
    Q.front->next=p->next;
    if(Q.rear=p) Q.rear=Q.front;
    delete p;
    return OK;
}

//取出队头元素
QElemType GetHead(LinkQueue Q)
{
    if(Q.front!=Q.rear)
        return Q.front->next->data;
}

void printQueue(LinkQueue Q)
{
    QNode *p = Q.front->next;
    if(!p) cout<<"空队列"<<endl;
    while (p)
    {
        if(p->next!=NULL)
            cout<<p->data<<"->";
        else
            cout<<p->data<<endl;
        p = p->next;
    }
}

int main()
{
    //1. 创建队列
    LinkQueue Q;
    if(InitQueue(Q))
        cout<<"创建空队列成功"<<endl;
    cout<<"入队操作："<<endl;
    cout<<"输入队元素个数:";
    int n,m;cin>>n;
    m = n;
    while(n>0)
    {
        cout<<"入队"<<m-n+1<<":";
        QElemType e;cin>>e;
        EnQueue(Q,e);
        n--;
    }
    cout<<"此时队列元素:"<<endl;
    printQueue(Q);
    cout<<endl;
    cout<<"取得队首元素:"<<GetHead(Q)<<endl;
    QElemType e;
    DeQueue(Q,e);
    cout<<"出队操作成功，且（队头）出队元素为"<<e<<endl;
    cout<<"此时队列元素:"<<endl;
    printQueue(Q);
}
