#include <stdio.h>
typedef unsigned char BYTE;
void main(){
	BYTE i = 81;
	while(i--){
		if(i/9%3==i%9%3)
			continue;
		printf("A=%d,b=%d\n",i/9+1,i%9+1);
	}
}