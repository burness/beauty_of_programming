#include <iostream>
using namespace std;

double* array_former_part_product(double array[],int n){
	double* former=new double[n+1];
	double temp=1.0;
	former[0]=1.0;
	for(int i=0;i<n;i++){
		temp*=array[i];
		former[i+1]=temp;
	}
	return former;
}
double* array_rearer_part_product(double array[],int n){
	double* rearer=new double[n+1];
	double temp=1.0;
	rearer[n]=1.0;
	for(int i=n-1;i>=0;i--){
		temp*=array[i];
		rearer[i]=temp;
	}
	return rearer;
}

double max_sub_array_product(double array[],int n){
	double* former=new double[n+1];
	double* rearer=new double[n+1];
	double* result=new double[n];
	former=array_former_part_product(array,n);
	rearer=array_rearer_part_product(array,n);
	for(int i=0;i<n;i++){
		result[i]=former[i]*rearer[i];
	}
	double max=result[0];
	for(int i=0;i<n;i++){
		if(max<result[i])
			max=result[i];
	}
	return max;
}


int main(){
	double array[]={1.0,2.0,3.0,4.0,5.0,6.0,7.0,8.0,9.0,10.0};
	cout<<"The max :"<<max_sub_array_product(array,sizeof(array)/sizeof(double));
}

