#include<iostream>
#include<stdlib.h>

#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

using namespace std;

typedef int Status;
typedef char SElemType;
typedef struct {
	SElemType *base;
	SElemType *top;
	int stacksize;
}SqStack;

//初始化
Status InitStack(SqStack &S) {
	S.base = new SElemType[MAXSIZE];

	if(!S.base) exit(OVERFLOW);

	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}
//入栈
Status Push(SqStack &S, SElemType e) {
    if(S.top-S.base==S.stacksize) return ERROR;
    *S.top++=e;
    return OK;
}
//出栈
Status Pop(SqStack &S, SElemType &e) {
    if(S.top==S.base) return ERROR;
    e=*--S.top;
    return OK;
}
//清空栈
Status ClearStack(SqStack &S) {
	if(S.base) S.top = S.base;
	return OK;
}
//取栈顶元素
Status GetTop(SqStack S,SElemType &e) {
	if(S.top==S.base) return ERROR;
	e = *(S.top-1);
	return OK;
}
//获得栈的长度
int StackLen(SqStack &S) {
    return (S.top-S.base);
}
//销毁栈
Status DestroyStack(SqStack &S){
    int len = S.stacksize;
    for(int i =0; i < len; i++){
        free(S.base);
        S.base++;
    }
    S.base = S.top = NULL;
    S.stacksize = 0;
    return OK;
}

int main() {
    //初始化
    SqStack S;
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
    cout<<"此时栈内"<<StackLen(S)<<"个元素"<<endl;
    //出栈
    SElemType getE1, getE2;
    if(Pop(S,getE1)==OK) cout<<getE1<<"出栈成功"<<endl;
    else cout<<"出栈失败"<<endl;
    //取栈顶元素
    if(GetTop(S,getE2)==OK) cout<<"栈顶元素为:"<<getE2<<endl;
    else cout<<"失败"<<endl;
    cout<<"此时栈内"<<StackLen(S)<<"个元素"<<endl;
    //清空
    int m;
    cout<<"输入1清空栈否则结束"<<endl;
    cin>>m;
    if(m==1) {
        if(ClearStack(S)==OK) {
            cout<<"栈已清空"<<endl;
            cout<<"此时栈内"<<StackLen(S)<<"个元素"<<endl;
        } else cout<<"清空失败"<<endl;
    } else {
        cout<<"操作结束"<<endl;
        cout<<"此时栈内"<<StackLen(S)<<"个元素"<<endl;
    }
    cout<<"销毁栈"<<endl;
    if(DestroyStack(S)==OK) {
        cout<<"销毁成功"<<endl;
        cout<<"此时栈内"<<StackLen(S)<<"个元素"<<endl;
    } else {
        cout<<"销毁失败"<<endl;
    }

    return 0;
}
