#include <iostream>
using namespace std;

int count(int num){
	int count=0;
	while(num){
		count+=num&0x01;
		num>>=1;
	}
	return count;
}


int main(){
	int num=21;
	cout<<"The # of 1 in the "<<num<<" is :"<<count(num)<<endl;
	return 1;
}