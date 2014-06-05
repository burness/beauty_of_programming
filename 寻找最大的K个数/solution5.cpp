//采用计数算法，一般用在已经N个数均为整数，且整数范围一定

#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;

int* random(int max,int num);

int* random(int max,int num){
	int *random_num=new int[num];
	srand((unsigned)time(NULL));
	for(int i=0;i<num;i++){
		random_num[i]=rand()%max;
	}
	return random_num;
}


int main(){
	int *random_num;
	int n=200,k=10;
	const int max=100;
	random_num=random(max,n);

	// 首先申请一个大小为max的数组
	int result[max]={0};
	for (int i=0;i<n;i++)
	{
		result[random_num[i]]++;
	}
	int count=0;
	for(int i=max-1;i>=0;i--){
		for(int j=result[i];j>=0&&count<k;j--){
			cout<<i<<" ";
			count++;
		}
		if(count>=k)
			break;
		
	}
	return 0;
}