#include <iostream>
#include<iomanip>
using namespace std;

// ����ĳ���
const int LENGTH = 20;

// ѡ����������������arr��������
void selectionSort(int arr[]) 
{
	int a=0;
    // ���ѭ��������������
    for (int i = 0; i < LENGTH - 1; i++) 
	{
        // �ڲ�ѭ������δ���򲿷ֵ���Сֵ
        int minIndex = i;
        for (int j = i + 1; j < LENGTH; j++) 
		{
            if (arr[j] < arr[minIndex]) 
			{
				a++;
                minIndex = j;
            }
        }
        // ����Сֵ���i��Ԫ�ؽ���λ��
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
	printf("ѡ��������ɣ��ܹ�������%d�ν���\n",a);
}
// ð����������������arr��������
void bubbleSort(int arr[])
{
	int a=0;
   // ���ѭ��������������
    for (int i = 0; i < LENGTH - 1; i++) 
	{
        // �ڲ�ѭ������ÿ�������еıȽϴ���
        for (int j = 0; j < LENGTH - i - 1; j++) 
		{
            // ���ǰһ�������ں�һ������������������λ��
            if (arr[j] > arr[j + 1]) 
			{
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
				a++;
            }
        }
    }
	printf("ð��������ɣ��ܹ�������%d�ν���\n",a);
}
int main() {
	// ѡ������
    int arr[] = { 9,6,22,1,5,10,210,2,21,34,12,45,99,14,12,567,123,32,47,100};
	printf("����Ϊ��");
	for (int i = 0; i < LENGTH; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    selectionSort(arr);
	// �������������
	printf("����������Ϊ��");
    for (int i = 0; i < LENGTH; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
	//ð������
	int brr[] = { 9,6,22,1,5,10,210,2,21,34,12,45,99,14,12,567,123,32,47,100};
	printf("����Ϊ��");
	for (int i = 0; i < LENGTH; i++) {
        std::cout << brr[i] << " ";
    }
    std::cout << std::endl;
	bubbleSort(brr);
    // �������������
	printf("����������Ϊ��");
    for (int i = 0; i < LENGTH; i++) {
        std::cout << brr[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}