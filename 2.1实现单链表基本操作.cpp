/*
编程实现单链表的基本操作：
建立单链表，
查找单链表，
插入单链表，
删除单链表；
*/
#include <iostream>

#define ElemType int
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100
using namespace std;

typedef int Status;
//定义存储结构
typedef struct LNode {
    ElemType data;
    struct LNode *next;
}LNode, *LinkList; //LinkList为指向结构体LNode的指针类型

//初始化
Status InitList(LinkList &L) {
    //构造一个空的单链表
    L = new LNode;    //新的结点作为头节点，用头指针L指向头结点
    L -> next = NULL; //头结点的指针域置空
    return OK;
}

//创建含有值的单链表：这种方法是逆序
Status CreateList_H(LinkList &L, int n) {
    //逆位序输入n个元素的值，建立带表头结点的单链表
    LNode *p = NULL;
    L = new LNode;
    L -> next = NULL;
    for(int i=0;i<n;i++) {
        p = new LNode;
        cin>>p->data;
        p -> next = L -> next;
        L -> next = p;
    }
    return OK;
}

//后插法插入指针：顺序值
Status CreateList_R(LinkList &L, int n) {
    LNode *r,*p = NULL;
    L = new LNode;
    L -> next = NULL;
    r = L;
    for(int i=0;i<n;i++) {
        p = new LNode;
        cin>>p->data;
        p -> next = NULL;
        r -> next = p;
        r = p;
    }
    return OK;
}

//取值
Status GetElem(LinkList L, int i, ElemType &e) {
    LNode *p = NULL;
    p = L -> next;
    int j = 1; //计数器
    while(p && j<i) {//直到p为空域，或者p指向第i个元素
        p = p -> next;
        ++j;
    }

    if(!p||j>i) return ERROR;
    e = p -> data;
    return OK;
}

//按照取值查找
LNode *LocateElem(LinkList L, ElemType e) {
    LNode *p = NULL;
    //在带头结点的单链表L中查找值为e的元素
    p = L -> next;
    while(p && p -> data!=e) {
        p = p -> next;
    }
    return p; //返回的是指为e的结点的地址p，如果查找失败p为null
}

//插入
Status ListInsert(LinkList &L, int i, ElemType e) {
    LNode *p,*s = NULL;
    //带头结点的单链表L中第i个位置插入值为e的新结点
    p = L;
    int j = 0;
    while(p && (j<i-1)) {
        p = p -> next;
        ++j;
    }
    if(!p||j>i-1) return ERROR;
    s = new LNode;
    s -> data = e;
    s -> next = p -> next;
    p -> next = s;
    return OK;
}

//删除
Status ListDelete(LinkList &L, int i) {
    LNode *p,*q = NULL;
    p = L;
    int j = 0;
    while((p->next)&&(j<i-1)) {
        p = p -> next;
        ++j;
    }
    if(!(p->next)||(j>i-1)) return ERROR;
    q = p -> next;
    p -> next = q -> next;
    delete q;
    return OK;
}

void PrintLinkList(LinkList &L) {
    LNode *p = NULL;
    p = L -> next;
    while(p) {
        if(p->next==NULL)
            cout<<p->data<<endl;
        else
            cout<<p->data<<"->";
        p = p -> next;
    }
}

void PrintCout() {
    cout<<"输入1创建空表"<<endl;
    cout<<"输入2逆序创建"<<endl;
    cout<<"输入3正序创建"<<endl;
}

int CreateListMain(LinkList &L) {
    int n;
    PrintCout();
    cin>>n;
    while(n)
    {
        int len = 0;
        switch(n)
        {
        case 1:
            InitList(L);
            break;
        case 2:
            cout<<"输入创建链表长度:";
            cin>>len;
            CreateList_H(L,len);
            break;
        case 3:
            cout<<"输入创建链表长度:";
            cin>>len;
            CreateList_R(L,len);
            break;
        default:
            cout<<"您的输入有误"<<endl;
            break;
        }
        if(n==1||n==2||n==3)
            break;
        else
            continue;
    }
    return 1;
}

void PrintCout_S() {
    cout<<"---------------------执行操作按照下方提示输入---------------"<<endl;
    cout<<"-********************输入1执行查找操作*********************-"<<endl;
    cout<<"-********************输入2执行插入操作*********************-"<<endl;
    cout<<"-********************输入3执行删除操作*********************-"<<endl;
    cout<<"-********************输入0退出*****************************-"<<endl;
    cout<<"------------------------------------------------------------"<<endl;
}

void DoMain(LinkList &L) {
    int n;
    PrintCout_S();
    cin>>n;
    while(n) {
        if(n==0)
            break;
        ElemType e;
        int i;
        switch(n)
        {
        case 1:
            cout<<"请输入要查找的值:";
            cin>>e;
            if(LocateElem(L, e)) cout<<"能查询得到"<<endl;
            else cout<<"链表中没有"<<endl;
            break;
        case 2:
            cout<<"输入要插入的值:";
            cin>>e;
            cout<<"输入要插入的第n个位置:";
            cin>>i;
            if(ListInsert(L,i,e))
                cout<<"插入成功"<<endl;
            else
                cout<<"插入失败"<<endl;
            break;
        case 3:
            cout<<"请输入要删除第_个元素:";
            cin>>i;
            if(ListDelete(L, i))
                cout<<"删除成功"<<endl;
            else
                cout<<"删除失败"<<endl;
            break;
        default:
            cout<<"您的输入有误"<<endl;
            break;
        }
        PrintLinkList(L);
        PrintCout_S();
        cin>>n;
    }
}


/*
建立单链表，
查找单链表，
插入单链表，
删除单链表；
*/

int main() {
    LinkList L;
    //创建链表
    if(CreateListMain(L)) {
        cout<<"创建成功"<<endl;
        PrintLinkList(L);
    } else {
        cout<<"ERROR"<<endl;
    }
    //查找，插入，删除
    DoMain(L);
    return 0;
}
