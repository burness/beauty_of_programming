#include <stdio.h>
struct i{
	unsigned char a:4;
	unsigned char b:4;
};


void main(){
	struct i test;
	for(test.a=1;test.a<=9;test.a++)
		for(test.b=1;test.b<=9;test.b++)
			if(test.a%3!=test.b%3)
				printf("A=%d, B=%d\n",test.a,test.b);

}