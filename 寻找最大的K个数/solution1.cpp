#include <iostream>
#include <stdio.h>
#include <time.h>
using namespace std;
// 使用快速排序先排序，然后取前k个数据
// return # of num between 0 and max-1
int* random(int max,int num);

int* random(int max,int num){
	int *random_num=new int[num];
	srand((unsigned)time(NULL));
	for(int i=0;i<num;i++){
		random_num[i]=rand()%max;
	}
	return random_num;
}
int comp( const void *a, const void * b)
{
	return *(int *)b-*(int *)a;
}
int* find_first_k_qsort(int *num,int n,int k);


int* find_first_k_qsort(int *num,int n,int k){
	int* result=new int[k];
	//对num进行快速排序
	qsort(num,n,sizeof(int),comp);
	for(int i=0;i<k;i++){
		result[i]=num[i];
	}
	return result;
}

int* find_first_k_select_sort(int *num,int n, int k){
	int* result=new int[k];
	// 只排序前K个有序
	for (int i=0;i<k-1;i++)
	{
		int index=i;
		int value=num[i];
		for(int j=i+1;j<n;j++){
			if(value<num[j]){
				index=j;
				value=num[j];
			}
		}
		num[index]=num[i];
		num[i]=value;
	}

	for(int i=0;i<k;i++){
		result[i]=num[i];
	}
	return result;
}


int main(){
	int *random_num;
	int n=200,max=100,k=10;
	random_num=random(max,n);
	int *result1,*result2;
	result1=find_first_k_qsort(random_num,n,k);
	result2=find_first_k_select_sort(random_num,n,k);
	cout<<"The first "<<k<<" num :";
	for (int i=0;i<k;i++)
	{
		cout<<result1[i]<<" ";
		//cout<<result2[i]<<endl;
	}
	cout<<" by qsort"<<endl;

	cout<<"The first "<<k<<" num :";
	for (int i=0;i<k;i++)
	{
		cout<<result2[i]<<" ";
	}
	cout<<" by select_sort "<<endl;

	return 1;
	
}