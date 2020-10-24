#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <vector>
/**
 *编程实现顺序表的基本操作：建立顺序表，修改顺序表，插入顺序表，删除顺序表
 *
 */
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

//将数组插入到顺序表
Status InsertElem(SqList &L, vector<ElemType> temp)
{
    for(int i=0;i<temp.size();i++) {
        ListInsert(L,L.length+1,temp[i]);
    }
    return OK;
}

void PrintList(SqList &L)
{
    if(L.length==0) cout<<"集合为空"<<endl;
    for(int i=0;i<L.length;i++)
    {
        if(i==L.length-1)
            cout<<L.elem[i]<<" Length="<<L.length<<endl;
        else
            cout<<L.elem[i]<<"->";
    }
}

//交集
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

    cout<<"交集：";
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

    cout<<"并集：";
    PrintList(L3);

    return L3;
}

Status uniqueElem(SqList &L1, SqList &L2)
{
    if(L1.length<L2.length) return ERROR;
    //L3复制L1
    SqList L3;
    InitList(L3);
    for(int i=0;i<L1.length;i++)
        ListInsert(L3,L3.length+1,L1.elem[i]);
    //主体循环
    int times=0;
    for(int i=0;i<L1.length;i++) {
        int j = LocateElem(L2,L1.elem[i]);
        //L1的元素在L2中存在，需要进行删除操作
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

    cout<<"差集：";
    PrintList(L3);

    return OK;
}

void Option(SqList L1, SqList L2)
{
    cout<<"请选择您需要进行的操作"<<endl;
    cout<<"输入1求并集"<<endl;
    cout<<"输入2求交集"<<endl;
    cout<<"输入3求差集"<<endl;
    cout<<"输入0退出操作"<<endl;
    int option;
    cin>>option;

    //并集
    //交集
    //差集: 并集-交集
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
            cout<<"您的输入有误，请重新输入"<<endl;
            break;
        }

        cout<<"请选择您需要进行的操作"<<endl;
        cout<<"输入1求并集"<<endl;
        cout<<"输入2求交集"<<endl;
        cout<<"输入3求差集"<<endl;
        cout<<"输入0退出操作"<<endl;
        cin>>option;
    }

}

int main()
{
    srand(time(NULL));
    //随机产生两个集合
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

    //插入到顺序表中
    InsertElem(L1,temp1);
    InsertElem(L2,temp2);

    PrintList(L1);
    PrintList(L2);

    Option(L1,L2);

    return 0;
}
