#include <iostream>
using namespace std;

int LIS(int d[], int n){
	int *B = new int[n];
	int i, left, right, mid, len = 1;
	B[0] = d[1]; //为了和上面的一致，我们从 1 开始计数吧:)
	for(i = 2; i <= n; ++i){
		left = 0, right = len;
		while(left <= right){
			mid = (left + right) / 2;
			if(B[mid] < d[i]) left = mid + 1; //二分查找 d[i]的插入位置
			else right = mid - 1;
		}
		B[left] = d[i]; //插入
		if(left > len) len++; //d[i]比现有的所有数字都大，所以 left 才会大于 len。
	}
	delete[] B;
	return len;
}


int main(){
	int array[]={1,-1,2,-3,4,-5,6,-7};
	cout<<"The length of the LIS is :"<<LIS(array,sizeof(array)/sizeof(int));
	return 0;
}