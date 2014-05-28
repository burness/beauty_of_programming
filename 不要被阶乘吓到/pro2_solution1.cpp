// 算法部分见readme的12部分
#include <iostream>
using namespace std;
int count_2(int N){//即N！的末尾0的个数
	int count=0;
	for (int i=1;i<=N;i++)
	{
		int j=i;
		while(j%2==0){
			count++;
			j=j/2;
		}
	}
	return count;
}


int main(){
	int N=21;
	cout<<"The num of the binary 0 at the end 21!:"<<count_2(N)<<endl;
}
