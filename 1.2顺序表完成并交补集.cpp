#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
/**
 *���ʵ��˳���Ļ�������������˳����޸�˳�������˳���ɾ��˳���
 *
 */
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
/*
Status InitList(SqList &L);
Status GetElem(SqList L, int i, ElemType &e);
int LocateElem(SqList L, ElemType e);
Status ChangeElem(SqList &L, int i, ElemType e);
Status ListInsert(SqList &L, int i, ElemType e);
Status ListDelete(SqList &L, int i);
void DelayElem(SqList &L);
Status CreateElem(SqList &L);
Status InsertElem(SqList &L, vector<ElemType> temp);
void PrintList(SqList &L);
Status CrossList(SqList &L1, SqList &L2);
SqList SameListElem(SqList &L1,SqList &L2);
SqList uniqueElem(SqList &L1,SqList &L2);
void Option(SqList &L1,SqList &L2);
*/

/*
void MergeList_Sq(SqList LA, SqList LB, SqList &LC) {
    LC.length = LA.length + LB.length;
    LC.elem = new ElemType[LC.length];
    pc = LC.elem;
    pa = LA.elem; pb = LB.elem;
    pa_last = LA.elem + LA.length -1;
    pb_last = LB.elem + LB.length -1;
    while(pa<=pa_last&&pb<=pb_last) {
        if(*pa<=*pb) *pc++ = *pa++;

    }
}*/


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

//delete2
void FundAndDelete(SqList &L, ElemType e)
{
	int j = 0;
	for(int i=0;i<L.length;i++)
	{
		if(L.elem[i]!=e) {
			L.elem[j] = L.elem[i];
			++j;
		}
	}
	L.length = j;
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

//��������뵽˳���
Status InsertElem(SqList &L, vector<ElemType> temp)
{
    for(int i=0;i<temp.size();i++) {
        ListInsert(L,L.length+1,temp[i]);
    }
    return OK;
}

void PrintList(SqList &L)
{
    if(L.length==0) cout<<"����Ϊ��"<<endl;
    for(int i=0;i<L.length;i++)
    {
        if(i==L.length-1)
            cout<<L.elem[i]<<" Length="<<L.length<<endl;
        else
            cout<<L.elem[i]<<"->";
    }
}

//����
SqList CrossList(SqList &L1, SqList &L2)
{
    SqList L3;
    InitList(L3);
    if(L1.length>L2.length) {
        for(int i=0;i<L2.length;i++)
            ListInsert(L3,L3.length+1,L2.elem[i]);
    } else {
        for(int i=0;i<L1.length;i++)
            ListInsert(L3,L3.length+1,L1.elem[i]);
    }
    for(int i=0;i<L3.length;i++) {
        int j = LocateElem(L1,L3.elem[i]);
        if(j==0)
            ListDelete(L3,i+1);
        else
            continue;
    }

    cout<<"������";
    PrintList(L3);

    return L3;
}

SqList SameListElem(SqList &L1,SqList &L2)
{
    SqList L3;
    InitList(L3);
    for(int i=0;i<L2.length;i++)
        ListInsert(L3,L3.length+1,L2.elem[i]);
    for(int i=0;i<L1.length;i++) {
        int j = LocateElem(L3,L1.elem[i]);
        if(j!=0)
            continue;
        else
            ListInsert(L3, L3.length, L1.elem[i]);
    }

    cout<<"������";
    PrintList(L3);

    return L3;
}

Status uniqueElem(SqList &L1, SqList &L2)
{
    if(L1.length<L2.length) return ERROR;
    //L3����L1
    SqList L3;
    InitList(L3);
    for(int i=0;i<L1.length;i++)
        ListInsert(L3,L3.length+1,L1.elem[i]);
    //����ѭ��
    int times=0;
    for(int i=0;i<L1.length;i++) {
        int j = LocateElem(L2,L1.elem[i]);
        //L1��Ԫ����L2�д��ڣ���Ҫ����ɾ������
        if(j==0)
            continue;
        else
        {
            int temp = i+1;
            temp-=times;
            ListDelete(L3,temp);
            times++;
        }
    }

    cout<<"���";
    PrintList(L3);

    return OK;
}

void Option(SqList L1, SqList L2)
{
    cout<<"��ѡ������Ҫ���еĲ���"<<endl;
    cout<<"����1�󲢼�"<<endl;
    cout<<"����2�󽻼�"<<endl;
    cout<<"����3��"<<endl;
    cout<<"����0�˳�����"<<endl;
    int option;
    cin>>option;

    //����
    //����
    //�: ����-����
    while(option!=0){
        SqList L5,L6,L3,L4;
        L5 = L1;
        L6 = L2;
        switch(option)
        {
        case 1:
            SameListElem(L1,L2);
            break;
        case 2:
            CrossList(L1,L2);
            break;
        case 3:
            L3 = SameListElem(L1,L2);
            L4 = CrossList(L1,L2);
            uniqueElem(L3,L4);
            break;
        default:
            cout<<"����������������������"<<endl;
            break;
        }

        cout<<"��ѡ������Ҫ���еĲ���"<<endl;
        cout<<"����1�󲢼�"<<endl;
        cout<<"����2�󽻼�"<<endl;
        cout<<"����3��"<<endl;
        cout<<"����0�˳�����"<<endl;
        cin>>option;
    }

}

int main()
{
    srand(time(NULL));
    //���������������
    int len1 = rand() % 10 + 1;
    int len2 = rand() % 10 + 1;
    vector<ElemType> temp1,temp2;
    for (int i = 0; i < len1; ++i)
    {
        temp1.push_back(i + 1);
    }
    for (int i = 0; i < len2; ++i)
    {
        temp2.push_back(i + 1);
    }

    random_shuffle(temp1.begin(), temp1.end());
    random_shuffle(temp2.begin(), temp2.end());

    SqList L1,L2;
    InitList(L1);
    InitList(L2);

    //���뵽˳�����
    InsertElem(L1,temp1);
    InsertElem(L2,temp2);

    PrintList(L1);
    PrintList(L2);

    Option(L1,L2);

    return 0;
}
