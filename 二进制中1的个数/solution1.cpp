#include <iostream>
using namespace std;

int count(int num){
	int count=0;
	while(num){
		if(num%2==1){
			count++;
		}
		num=num/2;
	}
	return count;
}


int main(){
	int num=21;
	cout<<"The # of 1 in the "<<num<<" is :"<<count(num)<<endl;
	return 1;
}