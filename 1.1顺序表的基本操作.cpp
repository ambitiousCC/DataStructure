/**
 *编程实现顺序表的基本操作：建立顺序表，修改顺序表，插入顺序表，删除顺序表
 *
 */
#include <iostream>
#define ElemType int
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

using namespace std;

//定义
typedef int Status;
typedef struct
{
    ElemType *elem;
    int length;
}SqList;

//初始化
Status InitList(SqList &L)
{
    L.elem = new ElemType[MAXSIZE];
    if(!L.elem) return OVERFLOW;
    L.length = 0;
    return OK;
}

//取值
Status GetElem(SqList L, int i, ElemType &e)
{
    if(i<1||i>L.length) return ERROR;
    e = L.elem[i-1];
    return OK;
}

//查找元素(返回第一个元素下标
int LocateElem(SqList L, ElemType e)
{
    for(int i=0; i<L.length; i++)
        if(L.elem[i]==e) return i+1;
    return 0;
}

//修改元素
Status ChangeElem(SqList &L, int i, ElemType e)
{
    if(i<1||i>L.length) return ERROR;
    L.elem[i-1] = e;
    return OK;
}

//插入元素
Status ListInsert(SqList &L, int i, ElemType e)
{
    if((i<1)||(i>L.length+1)) return ERROR;
    if(L.length==MAXSIZE) return ERROR;
    for(int j=L.length-1;j>=i-1;j--)
        L.elem[j+1] = L.elem[j];
    L.elem[i-1] = e;
    ++L.length;
    return OK;
}

//删除
Status ListDelete(SqList &L, int i)
{
    if((i<1)||(i>L.length)) return ERROR;
    for(int j=i;j<L.length;j++)
        L.elem[j-1] = L.elem[j];
    --L.length;
    return OK;
}

void DelayElem(SqList &L)
{
    for(int i=1;i<=L.length;i++) {
        ElemType e;
        GetElem(L,i,e);
        if(i==L.length)
            cout<<e<<"("<<i<<")"<<endl;
        else
            cout<<e<<"("<<i<<")"<<"->";
    }
}
//建立顺序表，修改顺序表，插入顺序表，删除顺序表

Status CreateElem(SqList &L)
{
    int n;
    cout<<"输入链表元素个数";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        ElemType e;
        cout<<"第"<<i+1<<"个元素:";
        cin>>e;
        ListInsert(L,i+1,e);
    }
    return OK;
}

void PrintStatus(SqList &L)
{
    cout<<"第一次操作，请初始化表"<<endl;
    CreateElem(L);
}

void PrintStatus_2(SqList &L)
{
    cout<<"目前L中元素:"<<endl;DelayElem(L);
    cout<<"输入1修改顺序表"<<endl;
    cout<<"输入2删除顺序表"<<endl;
    cout<<"输入3退出"<<endl;
}


int main()
{
    SqList L;
    int choices,i;
    InitList(L);
    PrintStatus(L);

    PrintStatus_2(L);
    cin>>choices;

    while(choices&&choices!=3) {
        switch(choices)
        {
        case 1:
            cout<<"输入需要修改的元素的index";
            cin>>i;
            cout<<"输入修正值:";
            ElemType e;
            cin>>e;
            if(ChangeElem(L,i,e))
                cout<<"ok"<<endl;
            else
                cout<<"error"<<endl;
            break;
        case 2:
            cout<<"输入需要删除的元素的下标";
            cin>>i;
            if(ListDelete(L,i))
                cout<<"ok"<<endl;
            else
                cout<<"error"<<endl;
            break;
        case 3:
            break;
        default:
            cout<<"输入不正确"<<endl;
            break;
        }

        if(choices!=3) {
            PrintStatus_2(L);
            cin>>choices;
        }
    }

    return 0;
}
