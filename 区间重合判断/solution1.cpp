#include <iostream>
#include <vector>

#define max 80
using namespace std;

// 区间的数据结构
class section
{
public:
	int begin,end;
};

bool is_coincide(section src,vector<section> dst){
	bool axis[80]={false};
	for(vector<section>::iterator index=dst.begin();index!=dst.end();index++){
		for(int i=(*index).begin;i<(*index).end;i++){
			axis[i]=true;
		}
	}
	for(int i=src.begin;i<src.end;i++){
		if(axis[i]==false){
			return false;
		}
	}
	return true;

}


int main(){
	section src,temp;
	src.begin=10;
	src.end=11;
	vector<section> dst;
	temp.begin=2;
	temp.end=3;
	dst.push_back(temp);
	temp.begin=1;
	temp.end=2;
	dst.push_back(temp);
	temp.begin=3;
	temp.end=9;
	dst.push_back(temp);

	cout<<"The src is concide?: "<<boolalpha<<is_coincide(src,dst);
	return 0;


	
}