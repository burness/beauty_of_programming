#include<iostream>  
using namespace std; 
const int MaxLength = 9;  
char c[10][10] = {"", "", "ABC", "DEF", "GHI", "JKL", "MNO", "PQRS", "TUV",
	"WXYZ"};  
int total[10] = {0,0,3,3,3,3,3,4,3,4};  

int main()  
{  
	int number[MaxLength] = {2,3,4}; //±¾ÀıÊäÈëÊı×Ö 2,3,4  
	int answer[MaxLength] = {0};  
	int len = 3;  

	while(true){  
		for(int i = 0; i < len; i++)  
			printf("%c", c[number[i]][answer[i]]);  
		printf("\n");  

		int k = len - 1;  
		while(k >= 0){  
			if(answer[k] < total[number[k]] - 1){  
				answer[k]++;  
				break;  
			}  
			else{  
				answer[k] = 0;  
				k--;  
			}  
		}  
		if(k < 0)  
			break;  
	}  
	return 0;  
}   