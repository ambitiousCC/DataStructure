#include <iostream>
#include <cstdlib>

#define MAXQSIZE 100
#define QElemType int
#define Status int
#define OK 1
#define ERROR 0
#define OVERFLOW -1
using namespace std;
typedef struct
{
    QElemType *base;
    int front;
    int rear;
}SqQueue;

//����ն���
Status InitQueue(SqQueue &Q)
{
    Q.base = new QElemType[MAXQSIZE];
    if(!Q.base) exit(OVERFLOW);
    Q.front=Q.rear=0;
    return OK;
}
//����г���
int QueueLength(SqQueue Q)
{
    return (Q.rear-Q.front+MAXQSIZE) % MAXQSIZE;
}

//���
Status EnQueue(SqQueue &Q,QElemType e)
{
    if((Q.rear+1)%MAXQSIZE==Q.front)
        return ERROR;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE;
    return OK;
}

//����
Status DeQueue(SqQueue &Q, QElemType &e)
{
    //ɾ����ͷ������
    if(Q.front==Q.rear) return ERROR;
    e=Q.base[Q.front];
    Q.front=(Q.front+1) % MAXQSIZE;
    return OK;
}

//getջ��Ԫ��
QElemType GetHead(SqQueue Q)
{
    if(Q.front!=Q.rear)
        return Q.base[Q.front];
}

void printQueue(SqQueue Q)
{
	int length = QueueLength(Q);
	for (int i = 0; i < length; i++)
	{
	    cout <<Q.base[(Q.front + i) % MAXQSIZE]<<" | ";
	}
	cout<<endl;
}

int main()
{
    //1. ��������
    SqQueue Q;
    if(InitQueue(Q))
        cout<<"�����ն��гɹ�"<<endl;
    cout<<"��ջ������"<<endl;
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
    cout<<"��ʱ����:"<<endl;
    printQueue(Q);
    cout<<endl;
    cout<<"ȡ�ö���:"<<GetHead(Q)<<endl;
    QElemType e;
    DeQueue(Q,e);
    cout<<"���Ӳ����ɹ����ҳ���Ԫ�أ�Ҳ�Ƕ�ͷ��Ϊ"<<e<<endl;
    cout<<"��ʱ����Ԫ��:"<<endl;
    printQueue(Q);
}
