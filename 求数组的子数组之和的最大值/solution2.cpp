#include <iostream>
using namespace std;
int MaxSum3(int *A,int beg,int end)
{
	if(beg==end)
		return A[beg-1];
	int mid = (beg+end)/2;
	// 最大和在左边的情况
	int left = MaxSum3(A,beg,mid);
	// 最大和在右边的情况
	int right = MaxSum3(A,mid+1,end);
	int sum = A[mid-1];
	int i = mid-1, j = mid+1;
	int maxsum = A[mid-1];
	// 第3中情况，最大和组合包括mid-1，mid
	while(i>=beg)
	{
		sum+= A[i-1];
		if(sum>maxsum)
			maxsum = sum;
		--i;
	}
	sum = maxsum;
	while(j<=end)
	{
		sum+=A[j-1];
		if(sum>maxsum)
			maxsum = sum;
		++j;
	}
	// 最后比较三种情况，（前面已经分为一个又一个比较小的数组来计算），最大和的那种情况即得到maxsum

	int max = left>right?left:right;
	max = max>maxsum?max:maxsum;
	return max;
}

int main(){
	int a[]={1,-2,3,5,-3,2};
	cout<<"The max sum is :"<<MaxSum3(a,0,sizeof(a)/sizeof(int)-1);
	return 0;
}