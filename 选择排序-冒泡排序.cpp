#include <iostream>
#include<iomanip>
using namespace std;

// 数组的长度
const int LENGTH = 20;

// 选择排序函数，将数组arr升序排序
void selectionSort(int arr[]) 
{
	int a=0;
    // 外层循环控制排序轮数
    for (int i = 0; i < LENGTH - 1; i++) 
	{
        // 内层循环查找未排序部分的最小值
        int minIndex = i;
        for (int j = i + 1; j < LENGTH; j++) 
		{
            if (arr[j] < arr[minIndex]) 
			{
				a++;
                minIndex = j;
            }
        }
        // 将最小值与第i个元素交换位置
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
	printf("选择排序完成，总共进行了%d次交换\n",a);
}
// 冒泡排序函数，将数组arr升序排序
void bubbleSort(int arr[])
{
	int a=0;
   // 外层循环控制排序轮数
    for (int i = 0; i < LENGTH - 1; i++) 
	{
        // 内层循环控制每轮排序中的比较次数
        for (int j = 0; j < LENGTH - i - 1; j++) 
		{
            // 如果前一个数大于后一个数，交换两个数的位置
            if (arr[j] > arr[j + 1]) 
			{
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
				a++;
            }
        }
    }
	printf("冒泡排序完成，总共进行了%d次交换\n",a);
}
int main() {
	// 选择排序
    int arr[] = { 9,6,22,1,5,10,210,2,21,34,12,45,99,14,12,567,123,32,47,100};
	printf("数组为：");
	for (int i = 0; i < LENGTH; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    selectionSort(arr);
	// 输出排序后的数组
	printf("排序后的数组为：");
    for (int i = 0; i < LENGTH; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
	//冒泡排序
	int brr[] = { 9,6,22,1,5,10,210,2,21,34,12,45,99,14,12,567,123,32,47,100};
	printf("数组为：");
	for (int i = 0; i < LENGTH; i++) {
        std::cout << brr[i] << " ";
    }
    std::cout << std::endl;
	bubbleSort(brr);
    // 输出排序后的数组
	printf("排序后的数组为：");
    for (int i = 0; i < LENGTH; i++) {
        std::cout << brr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}