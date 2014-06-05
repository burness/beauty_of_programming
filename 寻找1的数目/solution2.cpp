#include <iostream>
using namespace std;
/************************************************************************/
/* 算法原理见readme                                                     */
/************************************************************************/

long long Sum1s(long long n){
	long iCount=0;
	long iFactor=1;
	long iLowerNum=0;
	int iCurrNum=0;
	long iHigherNum=0;

	while(n/iFactor!=0){
		iLowerNum=n-(n/iFactor)*iFactor;
		iCurrNum=(n/iFactor)%10;
		iHigherNum=n/(10*iFactor);

		switch(iCurrNum){
		case 0:
			iCount+=iHigherNum*iFactor;
			break;
		case 1:
			iCount+=iHigherNum*iFactor+iLowerNum+1;
			break;
		default:
			iCount+=(iHigherNum+1)*iFactor;
			break;
		}
		iFactor*=10;

	}
	return iCount;
}


int main(){
	int n;
	cout<<"Enter the num of 1 that you want know that between 1 and it "<<endl;
	cin>>n;
	cout<<"The num of 1 between 1 and "<<n<<" is "<<Sum1s(n)<<endl;
}