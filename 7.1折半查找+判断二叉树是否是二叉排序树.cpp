#include <iostream>
#include <iomanip>
/*
*   1. д���۰���ҵĵݹ��㷨
*   2. д��һ���б�����������Ƿ�Ϊ�������������㷨
*/
#define KeyType int
#define InfoType int
using namespace std;

typedef struct{
    KeyType key;
    InfoType otherinfo;
}ElemType;

typedef struct{
    ElemType *R;
    int length;
}SSTable;

void InitSSTable(SSTable &ST, int length)
{
    KeyType key;
    InfoType info;
    ST.length = length;
    ST.R = new ElemType;
    for(int i=0;i<length;i++)
    {
        cout<<"����˳���ĵ�"<<i+1<<"��Ԫ��"<<endl;
        cin>>key;
        ST.R[i].key = key;
        ST.R[i].otherinfo = 0;
    }
}

//�۰���ҵĵݹ��㷨
int search_times = 0;
int Search_Bin(SSTable ST, KeyType key, int low, int high)
{
    search_times++;
    if(low<=high)
    {
        int mid = (low+high)/2;
        if(key==ST.R[mid].key)
            return mid;
        else if(key<ST.R[mid].key)
            Search_Bin(ST,key,low,mid - 1);
        else
            Search_Bin(ST,key,mid + 1,high);
    }
    else
    {
        return 0;
    }
}

void printTable(SSTable ST)
{
    cout<<"˳���ṹ��"<<endl;
    cout<<"index|key|otherinfo"<<endl;
    for(int i=0;i<ST.length;i++)
    {
        cout<<setw(5)<<i<<"|"<<setw(3)<<ST.R[i].key<<"|"<<setw(9)<<ST.R[i].otherinfo<<endl;
    }
}

int main()
{
    SSTable ST;
    cout<<"����˳���ĳ��ȣ�";
    int length;
    cin>>length;
    InitSSTable(ST,length);
    cout<<"˳����ӡ��"<<endl;
    printTable(ST);
    cout<<"������ҵ�Ԫ��:"<<endl;
    KeyType key;
    cin>>key;

    if(Search_Bin(ST,key,0,ST.length-1)==0)
    {
        cout<<"û�в鵽"<<endl;
        cout<<"���ҵĴ���Ϊ��"<<search_times<<endl;
    }
    else
        cout<<"index="<<Search_Bin(ST,key,0,ST.length-1)<<",key="<<ST.R[Search_Bin(ST,key,0,ST.length-1)].key<<",search_times="<<search_times<<endl;
    return 0;
}
