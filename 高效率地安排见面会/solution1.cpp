#include <iostream>
using namespace std;
const int N=3;// the # of the students
const int M=4; // the # of the meetings

// A:(1,2,3) B:(2,3,4) C:(2,3)
int meet[N][M]={
	{1,1,1,0},
	{0,1,1,1},
	{0,1,1,0},
};

int path[M][M]={
	{0,1,1,0},
	{1,0,1,1},
	{1,1,0,1},
	{0,1,1,0}
};


int color[M]={0,-1,-1,-1};

bool judge(int i, int j)//判断第i个节点，当涂j颜色的时候是否满足,返回false则表示与i节点相邻的存在颜色相同的
{
	for(int w=0;w<M;w++){
		if(path[i][w]){
			if(color[i]==color[w])
				return false;
		}
	}
	return true;
}

int arrange(){
	int num=0;//表示可以同时安排的会议的数目
	for(int i=1;i<M;i++){
		for(int j=0;j<M;j++){
			color[i]=j;
			if(judge(i,j)){
				break;
			}
		}
	}
	for(int i=0;i<M;i++){
		cout<< color[i]<<" ";
		if(num<color[i])
			num=color[i];
	}
	return num+1;
}


int main(){
	int time=5;
	int t=arrange();
	cout<<"花费总的时间："<<time*t<<endl;
	return 0;
}