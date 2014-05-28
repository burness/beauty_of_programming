#include <iostream>
using namespace std;

const int BEGIN=1;
const int END=2;
const int N=4;
struct Time{
	int type;
	int time;
};

Time times[N+N];
int cmp(const void* a, const void* b){
	return((Time*)a)->time-((Time*)b)->time;
}


void init(){
	for(int i=0;i<N+N;i++){
		cin>>times[i].time;
		if(i%2==0)
			times[i].type=BEGIN;
		else
			times[i].type=END;
	}
	qsort(times,N+N,sizeof(Time),cmp);

	for(int i=0;i<N+N;i++){
		cout<<times[i].time<<"type: "<<times[i].type<<" ";
	}
}


int arrange(){
	init();
	int usingcolor=0;
	int max=0;
	for(int i=0;i<N+N;i++){
		if(times[i].type==BEGIN){
			usingcolor++;
			if(max<usingcolor)
				max=usingcolor;

		}
		else
			usingcolor--;
	}
	return max;
}

int main(){
	int color=arrange();
	cout<<color<<endl;
	return 0;
}