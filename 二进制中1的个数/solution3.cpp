#include <iostream>
using namespace std;

int count(int num){
	int count=0;
	while(num){
		num&=(num-1);//每一次找到对应地最低位1
		count++;
	}
	return count++;
}


int main(){
	int num=21;
	cout<<"The # of 1 in the "<<num<<" is :"<<count(num)<<endl;
	return 1;
}