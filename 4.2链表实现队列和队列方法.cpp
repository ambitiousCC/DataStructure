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

//��ʼ��
Status InitQueue(LinkQueue &Q)
{
    Q.front=Q.rear=new QNode;
    Q.front->next=NULL;
    return OK;
}

//���
Status EnQueue(LinkQueue &Q,QElemType e)
{
    QNode *p = new QNode;
    p->data=e;
    p->next=NULL;
    Q.rear->next=p;
    Q.rear=p;
    return OK;
}

//����
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

//ȡ����ͷԪ��
QElemType GetHead(LinkQueue Q)
{
    if(Q.front!=Q.rear)
        return Q.front->next->data;
}

void printQueue(LinkQueue Q)
{
    QNode *p = Q.front->next;
    if(!p) cout<<"�ն���"<<endl;
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
    //1. ��������
    LinkQueue Q;
    if(InitQueue(Q))
        cout<<"�����ն��гɹ�"<<endl;
    cout<<"��Ӳ�����"<<endl;
    cout<<"�����Ԫ�ظ���:";
    int n,m;cin>>n;
    m = n;
    while(n>0)
    {
        cout<<"���"<<m-n+1<<":";
        QElemType e;cin>>e;
        EnQueue(Q,e);
        n--;
    }
    cout<<"��ʱ����Ԫ��:"<<endl;
    printQueue(Q);
    cout<<endl;
    cout<<"ȡ�ö���Ԫ��:"<<GetHead(Q)<<endl;
    QElemType e;
    DeQueue(Q,e);
    cout<<"���Ӳ����ɹ����ң���ͷ������Ԫ��Ϊ"<<e<<endl;
    cout<<"��ʱ����Ԫ��:"<<endl;
    printQueue(Q);
}
