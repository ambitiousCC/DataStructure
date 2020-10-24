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

//构造空队列
Status InitQueue(SqQueue &Q)
{
    Q.base = new QElemType[MAXQSIZE];
    if(!Q.base) exit(OVERFLOW);
    Q.front=Q.rear=0;
    return OK;
}
//求队列长度
int QueueLength(SqQueue Q)
{
    return (Q.rear-Q.front+MAXQSIZE) % MAXQSIZE;
}

//入队
Status EnQueue(SqQueue &Q,QElemType e)
{
    if((Q.rear+1)%MAXQSIZE==Q.front)
        return ERROR;
    Q.base[Q.rear]=e;
    Q.rear=(Q.rear+1)%MAXQSIZE;
    return OK;
}

//出队
Status DeQueue(SqQueue &Q, QElemType &e)
{
    //删除队头并返回
    if(Q.front==Q.rear) return ERROR;
    e=Q.base[Q.front];
    Q.front=(Q.front+1) % MAXQSIZE;
    return OK;
}

//get栈顶元素
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
    //1. 创建队列
    SqQueue Q;
    if(InitQueue(Q))
        cout<<"创建空队列成功"<<endl;
    cout<<"入栈操作："<<endl;
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
    cout<<"此时队列:"<<endl;
    printQueue(Q);
    cout<<endl;
    cout<<"取得队首:"<<GetHead(Q)<<endl;
    QElemType e;
    DeQueue(Q,e);
    cout<<"出队操作成功，且出队元素（也是队头）为"<<e<<endl;
    cout<<"此时队列元素:"<<endl;
    printQueue(Q);
}
