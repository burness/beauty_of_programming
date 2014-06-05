#include <iostream>
using namespace std;

const int N = 8 ;  
const int K = 4 ;  
   
 /* 
 利用二分的方法求取TOP k问题。 
 首先查找 max 和 min，然后计算出 mid = (max + min) / 2 
 该算法的实质是寻找最大的K个数中最小的一个,即找出第K大的数。  
  
  
 */  
   
 int find(int * a , int x) //查询出大于或者等于x的元素个数    
 {  
     int sum = 0 ;  
       
     for(int i = 0 ; i < N ; i++ )  
     {   
        if(a[i] >= x)  
          sum++ ;                  
     }  
      return sum ;  
 }  
   
 
 int getK(int * a , int max , int min) //最终max min之间只会存在一个或者多个相同的数字    
 {  
     while(max - min > 1)             //max - min的值应该保证比两个最小的元素之差要小    
      {  
        int mid = (max + min) / 2 ;  
        int num = find(a , mid) ;    //返回比mid大的数字个数    
        if(num >= K)                 //最大的k个数目都要比min值大    
           min = mid ;                 
        else  
           max = mid  ;  
      }  
      //cout<<"end"<<endl;  
      return min ;  
 }  
   
 int main()  
 {  
   int a[N] = {54, 2 ,5 ,11 ,554 ,65 ,33 ,2} ;    
   int x = getK(a , 554 , 2) ;   
   cout<<"The "<< K<<"th num is :"<<x<<endl ;      
   return 0 ;      
 }
