#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int two_num_sum_vec(vector<int> ivec, int sum,vector<int>& num1, vector<int>& num2 ){
	sort(ivec.begin(),ivec.end());
	for(int i=0,j=ivec.size()-1;i<j;){
		if(ivec[i]+ivec[j]==sum){
			num1.push_back(ivec[i]);
			num2.push_back(ivec[j]);
			i++;
		}
		else if(ivec[i]+ivec[j]<sum){
			i++;
		}
		else
			j--;
	}
	if(num1.size()!=0){
		return 1;
	}
	return 0;
}

int main(){
	vector<int> ivec,inum1,inum2;
	int sum=8;
	for(int i=10;i>0;i--){
		ivec.push_back(i);
	}
	cout<<two_num_sum_vec(ivec,sum,inum1,inum2);
	cout<<"The sum :"<<sum<<endl;
	cout<<"The num1 and num2 possible are:"<<endl;
	for (int i=0;i<inum1.size();i++)
	{
		cout<<inum1[i]<<" and "<<inum2[i]<<endl;
	}

	return 1;
}