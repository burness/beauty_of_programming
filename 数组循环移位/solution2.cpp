// 使用分块的逆序算法达到时间复杂度O(N)
#include <iostream>
using namespace std;

char* reverse(char* arr,int b,int e){
	for(;b<e;b++,e--){
		int temp=arr[e];
		arr[e]=arr[b];
		arr[b]=temp;
	}
	return arr;
}

char* right_shift(char* arr, int N, int k){
	k%=N;
	reverse(arr,0,N-k-1);
	reverse(arr,N-k,N-1);
	reverse(arr,0,N-1);
	return arr;
}

int main(){
	char array[]={'a','b','c','d','1','2','3','4'};
	char* dst=right_shift(array,sizeof(array)/sizeof(char),4);
	for(int i=0;i<sizeof(array)/sizeof(char);i++){
		cout<<" "<<dst[i];
	}
	return 0;

}