#include <iostream>
#include <string>
using namespace std;

int minValue(int t1, int t2, int t3){
	int mini;
	return mini=(mini=t1<t2?t1:t2)<t3?(mini=t1<t2?t1:t2):t3;
}

int calculatestringdistance(string strA, int pABegin, int pAEnd, string strB, int pBBegin, int pBEnd){
	if(pABegin>pAEnd){
		if(pBBegin>pBEnd)
			return 0;
		else
			return pBEnd-pBBegin+1;
	}
	if(pBBegin>pBEnd){
		if(pABegin>pAEnd)
			return 0;
		else
			return pAEnd-pAEnd+1;
	}
	if(strA[pABegin]==strB[pBBegin]){
		return calculatestringdistance(strA, pABegin+1, pAEnd,strB, pBBegin+1, pBEnd);
	}
	else{
		int t1=calculatestringdistance(strA, pABegin, pAEnd, strB, pBBegin+1, pBEnd);
		int t2=calculatestringdistance(strA,pABegin+1, pAEnd, strB, pBBegin, pBEnd);
		int t3=calculatestringdistance(strA,pABegin+1,pAEnd, strB, pBBegin+1,pBEnd);
		return minValue(t1,t2,t3)+1;
	}
}


int main(){
	string a("abcfe");
	string b("abcdf");
	int t1=3,t2=4,t3=1;
	cout<<"The distance between a and b :"<<calculatestringdistance(a,0,a.length()-1,b,0,b.length()-1);
	return 0;
}