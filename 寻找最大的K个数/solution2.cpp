#include <iostream>
#include <time.h>
using namespace std;

int* random(int max,int num){
	int *random_num=new int[num];
	srand((unsigned)time(NULL));
	for(int i=0;i<num;i++){
		random_num[i]=rand()%max;
	}
	return random_num;
}

void Swap(int* num1, int* num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}
int RandomInRange(int min, int max)
{
	int random = rand() % (max - min + 1) + min;
	return random;
}

int Partition(int data[], int length, int start, int end)
{
	if(data == NULL || length <= 0 || start < 0 || end >= length)
		throw new std::exception("Invalid Parameters");

	int index = RandomInRange(start, end);//随机去一个下标，比下标对应数字大的在一边，小的在另一边
	Swap(&data[index], &data[end]);//把下标对应的值作为判断大小对应标准的数字，并swap到最后，方便对比

	int big = start - 1;
	for(index = start; index < end; ++ index)
	{
		if(data[index] > data[end])
		{
			++ big;
			if(big != index)//当遍历中因为不满足data[index]>data[end]时，big停留在上一个满足条件的情况，在下一个满足条件时，big!=index满足
							//故需要交换次是的index和big对应的数，例如672154，前两个不进入此if块，但是经过2，1之后big=1,index=4，而此时满足
							// data[index]>data[end]，big++，需交换2，5则满足前面的大于4(不包括end)，后面的小于4最终为675124
				Swap(&data[index], &data[big]);
		}
	}

	++ big;
	Swap(&data[big], &data[end]);// 交换对应的big的数字与end的数字即最终得到675412

	return big;
}

void find_k_num_solution2(int* input, int n, int* output, int k)
{
	if(input == NULL || output == NULL || k > n || n <= 0 || k <= 0)
		return;

	int start = 0;
	int end = n - 1;
	int index = Partition(input, n, start, end);
	while(index != k - 1)
	{
		if(index > k - 1)
		{
			end = index - 1;
			index = Partition(input, n, start, end);
		}
		else// 小于k-1的部分
		{
			start = index + 1;
			index = Partition(input, n, start, end);
		}
	}

	for(int i = 0; i < k; ++i)
		output[i] = input[i];
}


int main(){
	int *random_num;
	int n=200,max=100,k=10;
	random_num=random(max,n);
	int* output=new int[k];
	find_k_num_solution2(random_num,n,output,k);
	for(int i=0;i<k;i++){
		cout<<output[i]<<" ";
	}
	cout<<endl;
	return 1;

}