# include <iostream>
# include <cstdlib>

#define ElementType int
using namespace std;

/*
    排序算法：
    1. *冒泡排序
    2. 插入排序
    3. 希尔排序
    4. 选择排序
    5. *快速排序
    6. 堆排序
    7. *归并排序
    8. 表排序
*/
void ERROR(string e) {
    cout<<"空间不足"<<endl;
}

//初始化数组
void InitElement(ElementType A[], int N)
{
    for(int i=0;i<N;i++) {
        cout<<"输入第"<<i+1<<"个元素:";
        cin>>A[i];
    }
}

//交换函数
void Swap(ElementType A[], int a, int b) {
	int temp = A[a];
	A[a] = A[b];
	A[b] = temp;
}
//冒泡排序
void Bubble_Sort(ElementType A[], int N) {
	for(int P=N-1;P>=0;P--) {
		int flag = 0;
		for(int i=0;i<P;i++)
			if(A[i]>A[i+1])
				Swap(A,i,i+1); //如果没有被执行，则这个序列本来就有序
				flag = 1; //标识发生了交换
		if(flag==0) break;
    }
}

//插入排序
void Insertion_Sort(ElementType A[], int N) {
    int i = 0;
	for(int P=1; P<N; P++) {
		int tmp = A[P]; //摸下一张牌
		for(i=P; i>0 && A[i-1]>tmp; i--)
			A[i] = A[i-1];
		A[i] = tmp; //新牌
	}
}

//快速排序
/*选中元：*/
ElementType Median3(ElementType A[], int Left, int Right) {
	int center = (Left + Right) /2;
	if(A[Left]>A[center])
		Swap(A,Left,center);
	if(A[Left]>A[Right])
		Swap(A,Left,Right);
	if(A[center]>A[Right])
		Swap(A,center,Right);
	//得到了左边最小，右边最大
	Swap(A,center,Right-1);//最后一个已经最大了，所以，就把中位数放在了最大数的左边一位，最后需要比较的就是A[left+1]~A[Right-2]
	return A[Right-1];
}
//递归程序
void Quicksort(ElementType A[], int Left, int Right) {
    int Cutoff = 4;
	if(Cutoff<=Right-Left) {
		int Pivot = Median3(A, Left, Right);
		int i = Left; int j = Right - 1;
		for(;;) {
			while(A[++i]<Pivot) {}
			while(A[--j]>Pivot) {}
			if(i<j)
				Swap(A,i,j);
			else break;
		}
		Swap(A,i,Right-1);//把藏住的主元放在位置
		Quicksort(A, Left, i-1);
		Quicksort(A, i+1, Right);
	} else {
		Insertion_Sort(A+Left, Right-Left+1);//小规模调用插入排序
	}
}

//符合标准接口要求主接口
void Quick_Sort(ElementType A[], int N) {
	Quicksort(A, 0, N-1);
}

//调整大顶堆
void PercDown(ElementType A[], int i, int N) {
	int temp = A[i];//取出当前元素
	for(int k=i*2+1; k<N; k=k*2+1) {
		if(k+1<N&&A[k]<A[k+1])
			k++;//左子结点小于右结点，k指向右子结点
		if(A[k]>temp) {//子结点大于父节点，直接赋值给父节点
			A[i] = A[k];
			i = k;
		} else {
			break;
		}
	}
	A[i] = temp;
}
//堆排序算法
void Heap_Sort(ElementType A[], int N) {
	for(int i=N/2; i>=0; i--)
		PercDown(A, i, N); //建立最大堆
	for(int i=N-1; i>0; i--) {
		Swap(A,0,i);
		PercDown(A, 0, i);
	}
}

//归并排序
/* L:左边起始位置，R:右边起始位置，RightEnd:右边终点位置*/
void Merge(ElementType A[], ElementType tempA[], int L, int R, int RightEnd) {
	int LeftEnd = R - 1;
	int temp = L;
	int NumElements = RightEnd - L + 1;//元素总个数
	//归并过程
	while(L<=LeftEnd&&R<=RightEnd) {
		if(A[L]<=A[R]) tempA[temp++] = A[L++];
		else tempA[temp++] = A[R++];
	}
	//多余就直接拼接
	while(L<=LeftEnd)
		tempA[temp++] = A[L++];
	while(R<=RightEnd)
		tempA[temp++] = A[R++];
	//L已经被使用过了
	for(int i=0;i<NumElements;i++,RightEnd--) {//RightEnd未被使用
		A[RightEnd] = tempA[RightEnd];
	}
}

void MSort(ElementType A[], ElementType tempA[], int L, int RightEnd) {
	int center;
	if(L<RightEnd) {
		center = (L+RightEnd) /2;
		MSort(A,tempA,L,center);
		MSort(A,tempA,center+1,RightEnd);
		Merge(A,tempA,L,center+1,RightEnd);
	}
}

void Merge_sort(ElementType A[], int N) {
	ElementType *tempA;
	tempA = (ElementType *)malloc(N*sizeof(ElementType));//申请空间
	if(tempA!=NULL) {
		MSort(A,tempA,0,N-1);
		free(tempA);
	} else {
		ERROR("空间不足");//报错方法
	}
}


//打印函数
void printElement(ElementType A[], int N) {
    for(int i=0; i<N; i++) {
        cout<<A[i]<<" ";
    }
    cout<<endl;
}

void CopyElem(ElementType A[], ElementType temp[], int N) {
    for(int i=0;i<N;i++) {
        temp[i] = A[i];
    }
}

int main()
{
    int N;
    cout<<"输入数组长度:";
    cin>>N;
    ElementType A[N];
    ElementType temp[N];

    InitElement(A, N);
    CopyElem(A,temp, N);

    //冒泡排序
    cout<<"origin:";
    printElement(temp, N);
    cout<<"冒泡排序："<<endl;
    Bubble_Sort(temp, N);
    printElement(temp, N);

    //快速排序
    CopyElem(A,temp, N);
    cout<<"origin:";
    printElement(temp, N);
    cout<<"快速排序："<<endl;
    Quick_Sort(temp, N);
    printElement(temp, N);

    //插入排序
    CopyElem(A,temp, N);
    cout<<"origin:";
    printElement(temp, N);
    cout<<"插入排序："<<endl;
    Insertion_Sort(temp,N);
    printElement(temp, N);

    //堆排序
    CopyElem(A,temp, N);
    cout<<"origin:";
    printElement(temp, N);
    cout<<"堆排序："<<endl;
    Heap_Sort(temp,N);
    printElement(temp, N);

    //归并排序
    CopyElem(A,temp, N);
    cout<<"origin:";
    printElement(temp, N);
    cout<<"归并排序："<<endl;
    Merge_sort(temp,N);

    printElement(temp, N);
    return 0;
}
