#include <iostream>
using namespace std;
int NumberOf1(const char* strN);
int PowerBase10(unsigned int n);
int NumberOf1Between1AndN(int n){
	if(n<=0)
		return 0;
	char strN[50];
	sprintf(strN,"%d",n);
	return NumberOf1(strN);
}

int NumberOf1(const char* strN){
	if(!strN||*strN<'0'||*strN>'9'||*strN=='\0')
		return 0;
	int first =*strN-'0';
	unsigned int length=static_cast<unsigned int>(strlen(strN));
	if (length==1&&first==0)
	{
		return 0;
	}
	if (length==1&&first>0)
	{
		return 1;
	}
	int numFirstDigit=0;
	// 比如21345 2>1故在万位上有10^4个万位为1的
	if(first>1)
		numFirstDigit=PowerBase10(length-1);
	else if(first==1)// 12345 first==1,万位为1的情况只有2345+1，str+1是首地址右移atoi(strN+1)==2345
		numFirstDigit=atoi(strN+1)+1;

	int numOtherDigit=first*(length-1)*PowerBase10(length-2);
	int numRecursive=NumberOf1(strN+1);

	return numFirstDigit+numOtherDigit+numRecursive;
}

int PowerBase10(unsigned int n){
	int result=1;
	for(unsigned int i =0;i<n;i++)
		result*=10;
	return result;
}


int main(){
	char *str="21345";
	cout<<"the 1s in 21345 is :"<<NumberOf1(str)<<endl;
}