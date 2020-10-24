#include <iostream>
#include <iomanip>
/*
*   1. 写出折半查找的递归算法
*   2. 写出一个判别给定二叉树是否为二叉排序树的算法
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
        cout<<"输入顺序表的第"<<i+1<<"个元素"<<endl;
        cin>>key;
        ST.R[i].key = key;
        ST.R[i].otherinfo = 0;
    }
}

//折半查找的递归算法
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
    cout<<"顺序表结构："<<endl;
    cout<<"index|key|otherinfo"<<endl;
    for(int i=0;i<ST.length;i++)
    {
        cout<<setw(5)<<i<<"|"<<setw(3)<<ST.R[i].key<<"|"<<setw(9)<<ST.R[i].otherinfo<<endl;
    }
}

int main()
{
    SSTable ST;
    cout<<"输入顺序表的长度：";
    int length;
    cin>>length;
    InitSSTable(ST,length);
    cout<<"顺序表打印："<<endl;
    printTable(ST);
    cout<<"输入查找的元素:"<<endl;
    KeyType key;
    cin>>key;

    if(Search_Bin(ST,key,0,ST.length-1)==0)
    {
        cout<<"没有查到"<<endl;
        cout<<"查找的次数为："<<search_times<<endl;
    }
    else
        cout<<"index="<<Search_Bin(ST,key,0,ST.length-1)<<",key="<<ST.R[Search_Bin(ST,key,0,ST.length-1)].key<<",search_times="<<search_times<<endl;
    return 0;
}
