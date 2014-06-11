#include <iostream>
using namespace std;
bool iseven(int x){
	if(x%2==0)
		return true;
	else
		return false;
}
int gcd(int x, int y){
	if(x<y)
		return gcd(y,x);
	if(y==0){
		return x;
	}
	else{
		if(iseven(x)){
			if(iseven(y))
				return (gcd(x>>1,y>>1)<<1);
			else
				return gcd(x>>1,y);

		}
		else{
			if(iseven(y))
				return gcd(x,y>>1);
		
			else
				return gcd(y,x-y);
		}
	}
}
int main(){
	int x=42,y=30;
	cout<<gcd(x,y)<<endl;
}
