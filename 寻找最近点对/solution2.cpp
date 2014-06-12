#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

int comp(const void *a, const void *b){
	return *(double *)a-*(double *)b;
}

double MiniDifference(vector<double> dVec,int n, int& minNum1,int& minNum2){
	//sort(dVec.begin(),dVec.size(),comp);
	sort(dVec.begin(),dVec.end());
	double fmindiff=fabs(dVec[0]-dVec[1]);
	for(int i=0;i<dVec.size()-1;i++){
		double temp=fabs(dVec[i]-dVec[i+1]);
		if(fmindiff>temp){
			fmindiff=temp;
			minNum1=dVec[i];
			minNum2=dVec[i+1];
		}

	}
	return fmindiff;
}


int main(){
	vector<double> dvec;
	srand((int) time(NULL));
	int n=10;
	for(int i=0;i<10;i++){
		double temp=rand()%20;
		dvec.push_back(temp);
	}
int minNum1=dvec[0],minNum2=dvec[1];

	cout<<"The mini difference in arr is :"<<MiniDifference(dvec,dvec.size(),minNum1,minNum2);
	cout<<"the point is "<<minNum1<<" and "<<minNum2<<endl;
}
