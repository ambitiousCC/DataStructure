#include<iostream>
#include<cstdlib>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

using namespace std;

typedef int Status;
typedef char SElemType;
typedef struct StackNode {
    SElemType data;
    struct StackNode *next;
}StackNode,*LinkStack;

//初始化
Status InitStack(LinkStack &S) {
	S=NULL;
	return OK;
}

//入栈
Status Push(LinkStack &S, SElemType e) {
    StackNode *p = new StackNode;
    p->data = e;
    p->next = S;
    S=p;
    return OK;
}

//出栈
Status Pop(LinkStack &S, SElemType &e) {
    if(S==NULL) return ERROR;
    e=S->data;
    StackNode *p=S;
    S=S->next;
    delete p;
    return OK;
}

//栈顶元素
SElemType GetTop(LinkStack S) {
    if(S!=NULL) return S->data;
}

//判断是否为空
bool StackEmpty(LinkStack S) {
	if(S==NULL) return true;
	else return false;
}

//清空栈
bool ClearStack(LinkStack &S) {
    StackNode *p,*q;
    p=S->next;
    while(p) {
        q = p;
        p = p -> next;
        free(q);
    }
    return true;
}

//长度
int LinkStackLen(StackNode *head) {
    if(head==NULL||head->next==NULL) return 0;
    StackNode *p = head->next;
    int len = 1;
    while(p!=NULL) {
        len++;
        p=p->next;
    }
    return len;
}

int main() {
    //初始化
    LinkStack S;
    if(InitStack(S)==OK) cout<<"初始化成功"<<endl;
    else cout<<"初始化失败"<<endl;
    //入栈
    int n;
    cout<<"输入入栈元素个数:";
    cin>>n;
    int i=1;
    while(n>0) {
        SElemType e;
        cout<<"第"<<i<<"个元素:";
        cin>>e;
        if(Push(S,e)==OK) cout<<e<<"入栈成功"<<endl;
        else cout<<"入栈失败"<<endl;
        n--;
        i++;
    }
    cout<<"此时栈长:"<<LinkStackLen(S)<<endl;
    //出栈
    SElemType getE1, getE2;
    if(Pop(S,getE1)==OK) cout<<getE1<<"出栈成功"<<endl;
    cout<<"此时栈长:"<<LinkStackLen(S)<<endl;
    //取栈顶元素
    cout<<"栈顶元素为"<<GetTop(S)<<endl;
    cout<<"此时栈长:"<<LinkStackLen(S)<<endl;
    return 0;
}
