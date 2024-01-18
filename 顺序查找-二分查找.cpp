#include<iostream>
#include<iomanip>
using namespace std;

//数组输出函数
void Display(int *data,int n)
{	int i,colNum=0;
	for(i=0;i<n;i++)
	{	cout<<setw(4)<<data[i];
		colNum++;
		if(colNum==9)//每行按9列输出
		{	colNum=0;
			cout<<endl;
		}
	}
	cout<<endl;
}
//顺序查找
int SequenceSearch(int a[], int value, int n)
{
	int count=0;
	int i=0;
	while(i<n)
	{
		count++;
        if(a[i]==value)
		{
			printf("经过%d次查找,查找成功\n",count);
			printf("查找成功，位置为%d\n",i);
			return i;
		}
		i++;
	}
	if(i>=n) printf("查找失败\n");
}

//二分查找
int BinarySearch(int a[], int value, int n)
{
    int low, high, mid;
	int count=0;
    low = 0;
    high = n-1;
    while(low<=high)
    {
		count+=1;
        mid = (low+high)/2;
        if(a[mid]==value)
		{
			printf("经过%d次查找,查找成功\n",count);
			printf("位置为%d\n",mid);
            return mid;
		}
			
		if(a[mid]>value) {high = mid-1;}
		if(a[mid]<value) {low = mid+1;}
    }
	if(low>high){printf("查找失败\n");}
}

int main()
{	
	int value=0;
	int data[9]={2,3,5,8,9,11,12,16,18};
	Display(data,9);//输出搜索数组
	printf("请输入查询的值：");
	scanf("%d",&value);
	printf("二分查找法结果：\n");
	BinarySearch(data,value,9);
	printf("顺序查找结果：\n");
	SequenceSearch(data,value,9);
	return 0;
}