#include <iostream>
using namespace std;


int strlen_me(char *src){
	int len=0;
	while(*src!=NULL){
		len++;
		src++;
	}
	return len;
}

//strstr_me()返回dst在src第一次出现的位置，若没找到则返回NULL
char* strstr_me(char* src, char* dst){
	if((*src)==NULL||(*dst)==NULL)
		return NULL;
	char* p1=src;

	while(*p1!=NULL){
		if(strlen_me(p1)<strlen_me(dst)){
			break;
		}
		char* p2=dst;
		char* temp=p1;
		while(*p2!=NULL){
			if(*p2==*p1){
				p2++;
				p1++;
			}
			else{
				break;
			}
		}
		if(*p2==NULL)
			return temp;
		p1=temp+1;
	}
	return NULL;


}


int main(){
	char src[]="AABCD";
	char dst[]="CDAA";

	char src2[]="AABCDAABCD";
	
	if(strstr_me(src2,dst)==NULL){
		cout<<"dst不能被src循环移位包含"<<endl;
	}
	else{
		cout<<"dst能被src循环移位包含"<<endl;
	}
	return 0;
}