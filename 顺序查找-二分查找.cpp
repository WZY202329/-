#include<iostream>
#include<iomanip>
using namespace std;

//�����������
void Display(int *data,int n)
{	int i,colNum=0;
	for(i=0;i<n;i++)
	{	cout<<setw(4)<<data[i];
		colNum++;
		if(colNum==9)//ÿ�а�9�����
		{	colNum=0;
			cout<<endl;
		}
	}
	cout<<endl;
}
//˳�����
int SequenceSearch(int a[], int value, int n)
{
	int count=0;
	int i=0;
	while(i<n)
	{
		count++;
        if(a[i]==value)
		{
			printf("����%d�β���,���ҳɹ�\n",count);
			printf("���ҳɹ���λ��Ϊ%d\n",i);
			return i;
		}
		i++;
	}
	if(i>=n) printf("����ʧ��\n");
}

//���ֲ���
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
			printf("����%d�β���,���ҳɹ�\n",count);
			printf("λ��Ϊ%d\n",mid);
            return mid;
		}
			
		if(a[mid]>value) {high = mid-1;}
		if(a[mid]<value) {low = mid+1;}
    }
	if(low>high){printf("����ʧ��\n");}
}

int main()
{	
	int value=0;
	int data[9]={2,3,5,8,9,11,12,16,18};
	Display(data,9);//�����������
	printf("�������ѯ��ֵ��");
	scanf("%d",&value);
	printf("���ֲ��ҷ������\n");
	BinarySearch(data,value,9);
	printf("˳����ҽ����\n");
	SequenceSearch(data,value,9);
	return 0;
}