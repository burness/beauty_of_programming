#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int two_num_sum_vec(vector<int> ivec, int sum,vector<int>& num1, vector<int>& num2 ){
	// First: sort ivec
	sort(ivec.begin(),ivec.end());
	// for ivec[i] to find that the sum-ivec[i] is in this ivec
	for (vector<int>::iterator index=ivec.begin();index!=ivec.end();index++)
	{
		vector<int>::iterator result=find(ivec.begin(),ivec.end(),sum-(*index));
		if(result!=ivec.end()){
			num1.push_back(*index);
			num2.push_back(sum-(*index));
		}
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