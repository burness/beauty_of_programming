#include <iostream>
#include <vector>
using namespace std;

// 将每次结果保存在一个vector中，然后计算新的项使用之前两项进行计算

long long Fibonacci(int n){
	vector<long long> Iarray;
	Iarray.push_back(0);
	Iarray.push_back(1);
	if(n<0){
		cout<<"n<0 is error"<<endl;
		return -1;
	}
	for(int i=2;i<=n;i++){
		long long temp=Iarray[i-2]+Iarray[i-1];
		Iarray.push_back(temp);
	}
	return Iarray[n];
}

int main(){
	int n=10;
	cout<<"The "<<n<<"st num in the Fibonacci list is :"<<Fibonacci(100)<<endl;
}