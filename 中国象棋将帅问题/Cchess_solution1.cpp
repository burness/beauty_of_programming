#include <stdio.h>
#define  HALF_BITS_LENGTH 4
#define FULLMASK 255
#define LMASK (FULLMASK << HALF_BITS_LENGTH)
#define RMASK (FULLMASK >> HALF_BITS_LENGTH)

#define  RSET(b,n)(b=((LMASK&b)|(n)))
#define  LSET(b,n)(b=((RMASK&b)|((n)<<HALF_BITS_LENGTH)))

#define RGET(b)(RMASK&b)
#define LGET(b)((LMASK&b)>>HALF_BITS_LENGTH)
#define GRIDW 3

int main(){
	unsigned char b;
	for(LSET(b,1);LGET(b)<=GRIDW*GRIDW;LSET(b,(LGET(b)+1)))
		for(RSET(b,1);RGET(b)<=GRIDW*GRIDW;RSET(b,(RGET(b)+1)))
			if(LGET(b)%GRIDW!=RGET(b)%GRIDW)
				printf("A=%d, B=%d\n",LGET(b),RGET(b));
	return 0;

}