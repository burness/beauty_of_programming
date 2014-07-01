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


bool is_include(char* src, char* dst){
	int len=strlen_me(src);
	for(int i=0;i<len;i++){
		char tempchar=src[0];
		for(int j=0;j<len-1;j++){
			src[j]=src[j+1];
		}
		src[len-1]=tempchar;
		if(strstr_me(src,dst)!=NULL){
			return true;
		}
	}
	return false;
}

int main(){
	char src[]="ABCD";
	char dst[]="ACBD";

	/*char* c=strstr_me(src,dst);
	if(c==NULL){
		cout<<"NULL";
	}
	else
		cout<<c<<endl;*/
	
	bool isOK=is_include(src,dst);
	cout<<"dst是否被循环移位包含？"<<boolalpha<<isOK<<endl;
}