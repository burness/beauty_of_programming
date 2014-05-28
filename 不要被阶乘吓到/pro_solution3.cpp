//含有质因数2的个数等于N减去N的二进制表示中1的个数
// 算法部分见readme的12部分
#include <iostream>
using namespace std;

int count_bin_1(int num){
	int count=0;
	while(num){
		num&=(num-1);//每一次找到对应地最低位1
		count++;
	}
	return count;
}

int count_2(int N){//即N！的末尾0的个数
	int count=0;
	count=N-count_bin_1(N);
	return count;
}


int main(){
	int N=21;
	cout<<"The num of the binary 0 at the end 21!:"<<count_2(N)<<endl;
}
