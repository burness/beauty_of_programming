#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

//快速找出仅出现一次的ID，每个ID是小于10e的整数，ID列表放在了data.txt中（ID一般是成对出现）
//如何设计程序快速找出那个仅出现一次的ID
//算法：对所有的ID进行异或操作，X异或X=0，X异或0=X，最后得到的数字即为仅出现一次的ID


// 1，设计一个从txt读入数据的函数，因为id是小于10e的整数，故令其为long long型
// 注意点 传入vector<long long>&以免值传递时，尽管函数内部有值存入vector但是在函数离开之后会还原，使用&引用则不会
int read_from_txt(const char* file_path,vector<long long> &l_vec){
	ifstream fin(file_path);
	if(!fin)
	{
		cerr<<"Can't open"<<file_path<<endl;
		return -1;
	}
	while(!fin.eof()){
		long long ltemp;
		fin>>ltemp;
		l_vec.push_back(ltemp);
	}
	fin.close();
	return 1;
	
}

long long fast_find_num_once(vector<long long> & l_vec){
	long long xor=0;
	for(vector<long long>::iterator index=l_vec.begin();index!=l_vec.end();index++)
	{
		xor=xor^(*index);
	}
	return xor;
}
// 假如机器记录ID都是双机备份，即每条记录在文件中有两个记录项，丢失一条记录即在数据中找仅出现一次的ID，即fast_find_num_once的功能
// 但是可能丢失两条记录
// 丢失记录情况有两种：1，两个记录恰好完全相同，也就是说现在记录文件中所有异或操作为0；
// 2，另外一种是，两条记录不同，也就是说，有两个只出现一次的记录，那么如何找出这两个只
// 出现一次的记录呢？分析可能对所有记录求异或后部为0，即其中必定有某位为1，我们不妨据此
// 将原有数据分为两个，该位为1的与该位不为1的，然后分别对这两类做异或处理，即得到两个记
// 录制有一次的ID
int fast_find_ID_lost_twice(vector<long long> & l_vec,long long &x_A,long long &x_B){
	if(l_vec.empty())
		return 0;
	long long xor=fast_find_num_once(l_vec);
	//这里是两个丢失的不是相同记录,找到xor的位上第一个为1的，如果两个丢失的为相同记录，则
	if(xor==0){
		// 利用所有ID之和-现在所有正常运行ID之和
		// x_A=x_B=(sum-sum_current)/2;
		// 因为这里是很大的数相加，涉及到大数相加的算法，一般大数相加采用位的方法，还是蛮复杂的
		// 这里暂时不给出 前面看书的时候有涉及到，
	}
	else{
	int k=0;
	while(xor){
		if(xor%2==1)
			break;
		k++;
		xor=xor>>1;
	}
	for(vector<long long>::iterator index=l_vec.begin();index!=l_vec.end();index++){
		if ((*index>>k)%2==0)
		{
			x_A=x_A^(*index);
		}
		else
			x_B=x_B^(*index);
	}
	return 1;
	}
}

int main(int argc,char * argv[]){
	//char* file_path="data.txt";
	char* file_path="data2.txt";
	vector<long long> long_vec;
	if(read_from_txt(file_path,long_vec)!=1){
		cerr<<"error happened!"<<endl;
	}

	// 现在txt文本数据存入到long_vec了
	//cout<<"The num appear once is :"<<fast_find_num_once(long_vec)<<endl;
	long long x_A=0;
	long long x_B=0;
	fast_find_ID_lost_twice(long_vec,x_A,x_B);
	cout<<"The num appear once is :"<<x_A<<" and "<<x_B<<endl;

}