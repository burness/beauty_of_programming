#include <iostream>
using namespace std;

int gcd(int x, int y){
	if(x<y)
		return gcd(y,x);
	if(y==0)
		return x;
	else
		return gcd(x-y,y);
}

int main(){
	int x=42,y=30;
	cout<<gcd(42,30)<<endl;
	return 1;
}