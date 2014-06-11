//辗转法f(x,y)=f(y,x%y),不必保证x>=y因为当x<y时下一步迭代时，x=上一次的y，y等于上一次的x
#include <iostream>
using namespace std;
int gcd(int x, int y){
	return (!y)?x:gcd(y,x%y);
}

int main(){
	int x=30,y=42;
	int a=gcd(x,y);
	cout<< a<<endl;
}