#include <iostream>
using namespace std;

//假定ID类型为int
// find()，candidate就是id中超过一半的，使用nTimes代表存在次数，不同的相消，相同的积累,这段程序的逻辑就是
// 每次删除不同的，但是在程序的编写上并没有真的删除数据，而是用了一个candidate和对应的nTimes来模拟对应的过程
// 也就是for循环的过程
int find(int* id, int N){
	int candidate;
	int nTimes,i;
	for(i=nTimes=0;i<N;i++){
		if(nTimes==0){
			candidate=id[i],nTimes=1;
		}
		else{
			if(candidate==id[i]){
				nTimes++;
			}
			else
				nTimes--;
		}
	}
	return candidate;
}

int main(){
	int a[]={1,2,3,4,5,1,1,1,1,1};
	cout<<"The half more num is :"<<find(a,sizeof(a)/sizeof(int));
	return 1;
}
