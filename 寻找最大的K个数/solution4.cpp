//堆排序：解决数据量特别大的时候，不能全部装入内存
#include <iostream>
using namespace std;

void heapifymin(int array[], int i, int size){
	if(i<size){
		int left=2*i+1;
		int right=2*i+2;
		int smallest=i;
		// 找到最小节点
		if(left<size){
			if(array[smallest]>array[left])
				smallest=left;
		}
		if(right<size){
			if(array[smallest]>array[right]){
				smallest=right;
			}
		}
		// 开始父节点和最小的子节点互换
		if(smallest!=i){
			int temp=array[smallest];
			array[smallest]=array[i];
			array[i]=temp;
			// 迭代，以当前最小节点为父节点
			heapifymin(array, smallest, size);
		}
	}
}
// 建立最小堆从最后一个节点开始建起
void min_heapify(int array[], int size){
	for(int i=size-1;i>=0;i--)
		heapifymin(array,i,size);
}

void findmax(int array[], int k, int size, int kMax[]){
	for(int i=0;i<k;i++)
		kMax[i]=array[i];
	// 调整堆
	min_heapify(kMax,k);
	cout<<"最小堆如下所示："<<endl;
	for(int i=0;i<k;i++)
		cout<<kMax[i]<<" ";
	cout<<endl;
	for(int j=k;j<size;j++){
		// 如果大于堆中最小的数，则交换
		if(array[j]>kMax[0]){
			int temp=kMax[0];
			kMax[0]=array[j];
			array[j]=temp;
			// 交换后可能破坏最小堆结构，因而要重新调整最小堆
			min_heapify(kMax,k);
		}
	}
}

int main(){
	int a[]={10,23,8,2,52,35,7,1,12};
	int length=sizeof(a)/sizeof(int);
	int k=4;
	int* kMax=new int[k];
	findmax(a,k,length,kMax);
	cout<<"最大的"<<k<<"个数如下所示：";
	for(int i=0;i<k;i++)
		cout<<kMax[i]<<" ";
	cout<<endl;
	return 0;
}


