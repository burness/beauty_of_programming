#include <iostream>
using namespace std;


// K<N(一般情况)，复杂度为O(KN)
char* right_shift(char* arr, int N, int K){
	while(K--){
		char Temp=arr[N-1];
		for(int i=N-1;i>0;i--){
			arr[i]=arr[i-1];
		}
		arr[0]=Temp;
	}

	return arr;
}
// K>N or K>>N(复杂度为O(N^2)
char* right_shift2(char* arr, int N, int K){
	K%=N;
	while(K--){
		int temp=arr[N-1];
		for(int i=N-1;i>0;i--)
			arr[i]=arr[i-1];
		arr[0]=temp;
	}
	return arr;
}

int main(){
	char array[]={'a','b','c','d','1','2','3','4'};
	char* dst=right_shift(array,sizeof(array)/sizeof(char),4);
	char* dst2=right_shift2(array,sizeof(array)/sizeof(char),4);
	for(int i=0;i<sizeof(array)/sizeof(char);i++){
		cout<<" "<<dst[i];
		cout<<" "<<dst2[i];
	}
	return 0;

}