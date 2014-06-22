#include <iostream>
using namespace std;

int MaxSum(int* A,int n){
	int maximum=INT_MIN;
	int sum;
	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			sum=0;
			for(int k=i;k<=j;k++)
			{
				sum+=A[k];
			}
			if(sum>maximum)
				maximum=sum;
		}
	}
	return maximum;

}
// a better implementation
int MaxSum2(int* A, int n){
	int maximum=INT_MIN;
	int sum;
	for(int i=0;i<n;i++){
		sum=0;
		for(int j=i;j<n;j++){
			sum+=A[j];
			if (sum>maximum)
			{
				maximum=sum;
			}
		}
	}
	return maximum;
}

int main(){
	int a[]={1,-2,3,5,-3,2};
	cout<<"The max sum is :"<<MaxSum(a,sizeof(a)/sizeof(int))<<"	"<<MaxSum2(a,sizeof(a)/sizeof(int));
	return 0;
}