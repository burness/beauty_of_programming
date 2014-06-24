#include <iostream>
using namespace std;


int Max(int LIS[], int n){
	int max=INT_MIN;
	for(int i=0;i<n;i++){
		if(LIS[i]>max){
			max=LIS[i];
		}
	}
	return max;
}

int LIS(int array[], int n){
	int* LIS=new int[n];
	for (int i=0;i<n;i++)
	{
		LIS[i]=1;
		for (int j=0;j<i;j++)
		{
			if(array[i]>array[j]&&LIS[j]+1>LIS[i]){
				LIS[i]=LIS[j]+1;
			}
		}
	}
	return Max(LIS,n);
}

int main(){
	int array[]={1,-1,2,-3,4,-5,6,-7};
	cout<<"The length of the LIS is :"<<LIS(array,sizeof(array)/sizeof(int));
	return 0;
}