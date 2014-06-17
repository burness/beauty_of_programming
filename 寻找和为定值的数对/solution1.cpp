// 穷举法
#include <iostream>
#include <vector>
using namespace std;

// 这个函数只能找到第一个和为sum的数对
int two_num_sum(int arr[], int n,int & num1, int & num2,int sum){

	for(int i=0;i<n;i++){
		for(int j=i;j<n;j++){
			if(arr[i]+arr[j]==sum){
				num1=arr[i];
				num2=arr[j];
				return 1;
				
			}
		}
	}
	return 0;
}
int two_num_sum_vec(vector<int> ivec, int sum,vector<int>& num1, vector<int>& num2 ){
	for(vector<int>::iterator index=ivec.begin();index!=ivec.end();index++){
		for(vector<int>::iterator index2=index+1;index2!=ivec.end();index2++){
			if(((*index)+(*index2))==sum){
				num1.push_back(*index);
				num2.push_back(*index2);
			}
		}
	}
	if (num1.size()!=0)
	{
		return 1;
	}
	return 0;
}

/*int main(){
	int test[]={1,2,3,4,5,6,7};
	int num1,num2,sum=8;
	//cout<<two_num_sum(test,sizeof(test)/sizeof(int),num1,num2,sum)<<""
	two_num_sum(test,sizeof(test)/sizeof(int),num1,num2,sum);
	cout<<" The sum:"<<sum<<endl;
	cout<<" and the num1 and num2:"<<num1<<" and "<<num2<<endl;
	return 1;
}*/

int main(){
	vector<int> ivec,inum1,inum2;
	int sum=8;
	for(int i=0;i<10;i++){
		ivec.push_back(i+1);
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