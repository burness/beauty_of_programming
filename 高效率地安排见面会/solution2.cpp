// 比如有四个面试，分别在时间段[1,5],[2,3],[3,4],[3,6],不同的面试在同一时间安排在同一个面试点
#include <iostream>
using namespace std;
const int N=4;
struct Time{
	int begin;
	int end;
};

bool forbit[N];//禁止数组，为false时，表示当前该颜色可以使用,
int maxcolors;

Time times[N];
int color[N]={0};
int cmp(const void * a, const void* b){
	return ((Time*)a)->begin-((Time*)b)->begin;
}

void init(){
	for(int i=0;i<N;i++){
		cin>>times[i].begin>>times[i].end;
	}
	qsort(times,N,sizeof(Time),cmp);
}

bool overlap(const Time &a ,const Time &b){
	if(b.begin>=a.begin&&b.begin<a.end){
		return true;
	}
	return false;
}

int arrange(){
	maxcolors=0;
	int i,j,k;
	for(i=0;i<N;i++){
		for(k=0;k<maxcolors;k++){
			forbit[k]=false;
		}

		//判断在i之前的节点是否与i节点有重合的地方
		for(j=0;j<i;j++){
			if(overlap(times[j],times[i])){//如果与之前的有重合的区间，那么这个点和之前那个点颜色不能相同也是就是forbit[i]置true
				forbit[color[j]]=true;
			}
		}
		for(k=0;k<maxcolors;k++){
			if(!forbit[k])
				break;
		}
		if(k<maxcolors)
			color[i]=k;
		else
			color[i]=maxcolors++;
	}
	return maxcolors;
}


int main(){
	init();
	int max=arrange();
	cout<<max<<endl;
	return 0;
}

