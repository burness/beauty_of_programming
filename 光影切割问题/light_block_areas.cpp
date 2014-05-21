#include <iostream>
using namespace std;
int count=0;
// function name:num_blocks_areas
// input£ºthe num of line and the point of intersection
// output: the num of the blocks areas
// eg: the num of lines: 2, the # of the point of intersection 1 return 4
int num_blocks_areas(int lines,int point_intersection){
	return lines+point_intersection+1;
}

// a better to found the num of the point of intersection by using the inversion number
// seen in fig 1-13 in the beauty of programming.
// function name: merge
// input: the char* required merge ,p the begins of the first part, q, the end of the first part, r: the end of the all char*
// output: NULL ,the function is to compute the num of inversion number by count which is a global var.
void merge(char* point_sequence, int p, int q, int r){
	int begin1,end1,begin2,end2,k;
	begin1=p;end1=q;
	begin2=q+1;end2=r;
	k=0;
	while(begin1<=end1&&begin2<=end2){
		if(point_sequence[begin1]-point_sequence[begin2]>0){
			begin2++;
			count+=q-begin1+1;
		}
		else{
			begin1++;
		}

	}

}

// function name: mergesort(the algorithm of the num intersection uses the merge sort algorithm)
// input: the points sequence of the right side seen in fig 1-13;
//		  the begin of the part and the end of the part
// output: NULL
void mergesort(char * point_sequence,int first, int last){
	int mid=(first+last)/2;
	if(first<last){
		mergesort(point_sequence,first,mid);
		mergesort(point_sequence,mid+1,last);
		merge(point_sequence,first,mid,last);
		//cout<<"The num of the point insersection"<<merge(point_sequence,first,mid,last)<<endl;
	}
}

// function name: getlength
// input: char* 
// output: the length of the char*
int getlength(char * points){
	int length=0;
	while(*points!='\0'){
		length++;
		points++;
	}
	return length;
}

int main(){
	int num_lines=3;
	char *points="cba";
	//cout<<"The num of the intersection points is: "<<mergesort(points,0,getlength(points)-1);
	mergesort(points,0,getlength(points)-1);
	cout<<"The num of the intersection points is :"<<count<<endl;
	cout<<"The block areas of the lines num:"<<num_lines<< " and the points intersection num:"<<count<<"'s blocks_areas num :"<< num_blocks_areas(num_lines,count)<<endl;
}
