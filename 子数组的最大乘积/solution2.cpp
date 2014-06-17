#include <iostream>
#include <limits>
using namespace std;

double array_product(double array[],int n){
	double temp=1.0;
	for(int i=0;i<n;i++){
		temp*=array[i];
	}
	return temp;
}

double array_n_1_product(double array[],int n){
	double temp=1.0;
	// 将第一个遇到的0以1.0替代
	for(int i=0;i<n;i++){
		if(array[i]==0){
			array[i]=1.0;
			break;
		}
	}
	temp=array_product(array,n);
	return temp;
}

double array_negative_product(double array[],int n){
	double temp=1.0;
	int temp_i;
	double negative_num_abs_min=(numeric_limits<double>::max)();
	//找到负数，并且保证其绝对值最小
	for(int i=0;i<n;i++){
		if(array[i]<0&&negative_num_abs_min>abs(array[i])){
			negative_num_abs_min=abs(array[i]);
			temp_i=i;
		}

	}
	array[temp_i]=1.0;
	double result=array_product(array,n);
	return result;
}

double array_postive_product(double array[],int n){
	double temp=1.0;
	int temp_i;
	double postive_num_min=(numeric_limits<double>::max)();
	//找到负数，并且保证其绝对值最小
	for(int i=0;i<n;i++){
		if(postive_num_min>array[i]){
			postive_num_min=array[i];
			temp_i=i;
		}

	}
	array[temp_i]=1.0;
	double result=array_product(array,n);
	return result;
}



double max_subarray_product(double array[],int n){
	double array_product_all=array_product(array, n);
	if(array_product_all==0){
		double Q=array_n_1_product(array,n);
		if(Q>=0)
			return Q;
		else
			return 0;
	}
	else if(array_product_all<0){
		//去掉绝对值最小的负数
		return array_negative_product(array,n);

	}
	else
		return array_postive_product(array,n);
}


int main(){
	double array[]={4.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
	cout<<"The max :"<<max_subarray_product(array,sizeof(array)/sizeof(double));
	return 0;
}