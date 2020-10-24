/**
 *���ʵ��˳���Ļ�������������˳����޸�˳�������˳���ɾ��˳���
 *
 */
#include <iostream>
#define ElemType int
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

using namespace std;

//����
typedef int Status;
typedef struct
{
    ElemType *elem;
    int length;
}SqList;

//��ʼ��
Status InitList(SqList &L)
{
    L.elem = new ElemType[MAXSIZE];
    if(!L.elem) return OVERFLOW;
    L.length = 0;
    return OK;
}

//ȡֵ
Status GetElem(SqList L, int i, ElemType &e)
{
    if(i<1||i>L.length) return ERROR;
    e = L.elem[i-1];
    return OK;
}

//����Ԫ��(���ص�һ��Ԫ���±�
int LocateElem(SqList L, ElemType e)
{
    for(int i=0; i<L.length; i++)
        if(L.elem[i]==e) return i+1;
    return 0;
}

//�޸�Ԫ��
Status ChangeElem(SqList &L, int i, ElemType e)
{
    if(i<1||i>L.length) return ERROR;
    L.elem[i-1] = e;
    return OK;
}

//����Ԫ��
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

//ɾ��
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
//����˳����޸�˳�������˳���ɾ��˳���

Status CreateElem(SqList &L)
{
    int n;
    cout<<"��������Ԫ�ظ���";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        ElemType e;
        cout<<"��"<<i+1<<"��Ԫ��:";
        cin>>e;
        ListInsert(L,i+1,e);
    }
    return OK;
}

void PrintStatus(SqList &L)
{
    cout<<"��һ�β��������ʼ����"<<endl;
    CreateElem(L);
}

void PrintStatus_2(SqList &L)
{
    cout<<"ĿǰL��Ԫ��:"<<endl;DelayElem(L);
    cout<<"����1�޸�˳���"<<endl;
    cout<<"����2ɾ��˳���"<<endl;
    cout<<"����3�˳�"<<endl;
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
            cout<<"������Ҫ�޸ĵ�Ԫ�ص�index";
            cin>>i;
            cout<<"��������ֵ:";
            ElemType e;
            cin>>e;
            if(ChangeElem(L,i,e))
                cout<<"ok"<<endl;
            else
                cout<<"error"<<endl;
            break;
        case 2:
            cout<<"������Ҫɾ����Ԫ�ص��±�";
            cin>>i;
            if(ListDelete(L,i))
                cout<<"ok"<<endl;
            else
                cout<<"error"<<endl;
            break;
        case 3:
            break;
        default:
            cout<<"���벻��ȷ"<<endl;
            break;
        }

        if(choices!=3) {
            PrintStatus_2(L);
            cin>>choices;
        }
    }

    return 0;
}
