#include <iostream>
#include <cmath>
using namespace std;

double MiniDifference(double arr[], int n, int &minX, int &minY){
	if(n<2)
		return 0;
	double fminDiff=fabs(arr[0]-arr[1]);
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			double temp=fabs(arr[i]-arr[j]);
			if(fminDiff>temp){
				fminDiff=temp;
				minX=i;
				minY=j;
			}
		}
	}
	return fminDiff;
}

int main(){
	double arr[]={3.0,4.0,5.0,4.5,3.5,2.5};
	int minX,minY;
	cout<<"The mini difference in arr is :"<<MiniDifference(arr,sizeof(arr)/sizeof(double),minX,minY);
	cout<<"the point is "<<minX<<" and "<<minY<<endl;
	return 0;

}