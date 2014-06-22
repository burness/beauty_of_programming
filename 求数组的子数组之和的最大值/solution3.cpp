// 具体分析见readme21算法三
// 举例说明：假设考虑数组的第一个元素A[0]，以及最大的一段数组(A[i],...,A[j])跟A[0]之间的关系
// 1,当0=i=j时，元素A[0]本身构成和最大的一段
// 2,当0=i<j时，和最大的一段从A[0]开始；
// 3,当0<i时，元素A[0]跟和最大的一段没有关系

#include <iostream>
using namespace std;

int max(int x,int y){
	return (x>y)? x:y;
}
// 需要额外两个数组空间
int MaxSum(int *A, int n){
	int* start=new int[n];
	int* all=new int[n];
	start[n-1]=A[n-1];
	all[n-1]=A[n-1];
	for(int i=n-2;i>=0;i--){
		start[i]=max(A[i],A[i]+start[i+1]);
		all[i]=max(start[i],all[i+1]);
	}
	return all[0];
}
// 不需要额外数组
int MaxSum2(int *A, int n){
	int nstart=A[n-1];
	int nAll=A[n-1];
	for(int i=n-2;i>=0;i--){
		nstart=max(A[i],nstart+A[i]);
		nAll=max(nstart,nAll);
	}
	return nAll;
}

int main(){
	int a[]={1,-2,3,5,-3,2};
	cout<<"The max sum is :"<<MaxSum(a,sizeof(a)/sizeof(int))<<"	"<<MaxSum2(a,sizeof(a)/sizeof(int));
	return 0;
}
