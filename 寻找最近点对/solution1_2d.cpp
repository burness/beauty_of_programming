#include <iostream>
#include <vector>
#include <time.h>
#include <math.h>
using namespace std;


class point{
public:
	double x;
	double y;
};

double MiniDifference(vector<point> pvec, int n,point& minPoint1,point&minPoint2){
	if(pvec.size()<2){
		return 0.0;
	}
	double fminDiff=fabs(pow(pvec[0].x-pvec[1].x,2)+pow(pvec[0].y-pvec[1].y,2));
	for (int i=0;i<n;i++)
	{
		for(int j=i+1;j<n;j++){
			double temp=fabs(pow(pvec[i].x-pvec[j].x,2)+pow(pvec[i].y-pvec[j].y,2));
			if(fminDiff>temp){
				fminDiff=temp;
				minPoint1.x=pvec[i].x;
				minPoint1.y=pvec[i].y;
				minPoint2=pvec[j];
			}
		}
	}
	return fminDiff;

}

int main(){
	vector<point> pVec;
	point temp;
	point minPoint1,minPoint2;
	int n=10;
	srand((int) time(NULL));
	for(int i=0;i<n;i++){
		temp.x=i;
		temp.y=i+rand();
		pVec.push_back(temp);
	}
	minPoint1=pVec[0];
	minPoint2=pVec[1];
	cout<<"The mini difference in arr is :"<<MiniDifference(pVec,pVec.size(),minPoint1,minPoint2);
	cout<<"the points are ("<<minPoint1.x<<","<<minPoint1.y<<")"<<" and "<<"("<<minPoint2.x<<","<<minPoint2.y<<")"<<endl;
	return 0;
}