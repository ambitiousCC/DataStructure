/*
编程实现单链表的基本操作
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

int CreateListMain(LinkList &L,bool isEmpty) {
    if(isEmpty)
    {
        InitList(L);
        return 1;
    }
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
            n=0;
            break;
        }
        if(n==1||n==2||n==3)
            break;
        else
            continue;
    }
    return 1;
}

void Inverse(LinkList &L) {
    LNode *p = L -> next;
    L -> next = NULL;
    while(p) {
        LNode *q = p -> next;
        p -> next = L -> next;
        L -> next = p;
        p = q;
    }
}

//查找中间结点:快指针比慢指针速度快两倍，快指针到达末结点时满指针指向中间结点
LNode* MidElem(LNode *head) {
    LNode *slow = head;
    LNode *fast = head -> next;
    while(fast!=NULL) {
        fast = fast -> next;
        if(fast == NULL)
            break;
        fast = fast -> next;
        slow = slow -> next;
    }
    return slow;
}

/**
 * 合并两个有序链表
 * @param l1
 * @param l2
 * @return
 */
LinkList Merge(LinkList &l1, LinkList &l2) {
    LinkList l;
    LNode *p = l;

    while (l1 != NULL && l2 != NULL) {
        if (l1->data < l2->data) {
            p->next = l1;
            l1 = l1->next;
        } else {
            p->next = l2;
            l2 = l2->next;
        }
        p = p->next;
    }

    if (l1 != NULL)
        p->next = l1;

    if (l2 != NULL)
        p->next = l2;

    return l->next;
}

/**
 * 链表的二路归并排序
 * @param head
 * @return
 */
LinkList sortList(LinkList &L) {
    //空链表或则只有一个结点,直接返回head
    LNode *head = L;
    if(head == NULL || head->next==NULL){
        return head;
    }

    //1. 将list 切分为两个部分
    LNode *prev=NULL, *slow=head, *fast=head;

    while (fast !=NULL && fast->next !=NULL){
        prev = slow;
        slow = slow->next;//slow指针后移一个数据
        fast = fast->next->next;//fast指针后移两个数据
    }

    prev->next = NULL;//将链表切断

    //分别排序前后两个部分
    LinkList l1 = sortList(head);
    LinkList l2 = sortList(slow);

    return Merge(l1, l2);
}
/*
// 改写原merge函数
LNode* Merge(LNode *left, LNode *right) {
    LinkList fin;
    LNode *p = fin;

    if(left->data<right->data) {
        p = left;
        left = left -> next;
    } else {
        p = right;
        right = right -> next;
    }
    p -> next = NULL;
    while(left&&right) {
        if(left->data<right->data) {
            p -> next = left;
            left = left -> next;
        } else {
            p -> next = right;
            right = right -> next;
        }
        p = p -> next;
        p -> next = NULL;
    }
    if(left != NULL) p->next = left;
    if(right != NULL) p->next = right;
    cout<<"?"<<endl;
    return fin->next;
}
LNode* MergeList(LinkList &L) {
    if(L==NULL) return NULL;
    if(L->next==NULL) return L;
    LNode *head = L;
    //查找中间点
    //LNode *Mid = MidElem(head);
    LNode *prev = NULL;
    LNode *slow = head;
    LNode *fast = head -> next;

    while(fast!=NULL) {
        prev = slow;
        fast = fast -> next;
        if(fast == NULL)
            break;
        fast = fast -> next;
        slow = slow -> next;
    }
    prev->next = NULL;

    //分治：将链表拆分
    LNode *left = MergeList(head);
    LNode *right = MergeList(slow);
    LNode *fin = Merge(left,right);
    return fin;
}*/

//教材方法：将两个有序表合并
void MergeList_L(LinkList &La, LinkList &Lb, LinkList &Lc) {
    LNode *pa = La -> next;
    LNode *pb = Lb -> next;
    Lc = La;
    LNode *pc = Lc;
    int i = 1;
    while(pa&&pb) {
        if(pa->data<=pb->data) {
            pc -> next = pa;
            pc = pa;
            pa = pa -> next;
        } else {
            pc -> next = pb;
            pc = pb;
            pb = pb -> next;
        }
    }
    pc -> next = pa?pa:pb;
    delete Lb;
}


int main() {
    LinkList La,Lb,Lc;
    //LinkList L;
    //创建链表
    /*
    if(CreateListMain(L)) {
        cout<<"创建成功，这是原始链表："<<endl;
        PrintLinkList(L);
    } else {
        cout<<"ERROR"<<endl;
    }*/

    //创建链表
    cout<<"-创建A链表"<<endl;
    if(CreateListMain(La,false)) {
        cout<<"创建成功，这是A链表："<<endl;
        PrintLinkList(La);
    } else {
        cout<<"ERROR"<<endl;
    }
    cout<<"-创建B链表"<<endl;
    if(CreateListMain(Lb,false)) {
        cout<<"创建成功，这是B链表："<<endl;
        PrintLinkList(Lb);
    }
    CreateListMain(Lc,true);

    MergeList_L(La, Lb, Lc);
    cout<<"执行归并运算"<<endl;
    PrintLinkList(Lc);
    //实现归并运算
    /*
    LinkList fin = sortList(L);
    PrintLinkList(fin);
*/
    return 0;
}
