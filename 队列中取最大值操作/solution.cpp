#include <iostream>
using namespace std;
#define Type int
#define MAXN 1024
class stack{
public:
	stack(){
		stackTop=-1;
		maxStackItemIndex=-1;
	}
	void push(Type x){
		stackTop++;
		if(stackTop>=MAXN)
			;
		else{
			stackItem[stackTop]=x;
			if(x>max()){
				link2NextMaxItem[stackTop]=maxStackItemIndex;
				maxStackItemIndex=stackTop;
			}
			else
				link2NextMaxItem[stackTop]=-1;
		}
	}
	Type pop(){
		Type ret;
		if(stackTop<0){
			cout<<"Error, There is no element"<<endl;
		}else{
			ret=stackItem[stackTop];
			if(stackTop==maxStackItemIndex){
				maxStackItemIndex=link2NextMaxItem[stackTop];
			}
			stackTop--;
		}
		return ret;
	}
	Type max(){
		if(maxStackItemIndex>=0){
			return stackItem[maxStackItemIndex];
		}else{
			return -1;
		}
	}
	bool empty(){
		if(stackTop==-1)
			return true;
		else
			return false;
	}

private:
	int stackTop;
	Type stackItem[MAXN];
	int link2NextMaxItem[MAXN];//link2NextMaxItem[stackTop]保存的是[0-stackTop-1]最大值的index，为了后面在删除栈顶元素，并且栈顶元素是最大的时候使用
	//比如插入1->2->3 link2NextMaxItem内容分别为-1,0,1
	int maxStackItemIndex;
};

// 用两个栈有效地表示队列
class queue{
public:
	Type MaxValue(Type x, Type y){
		return x>y?x:y;
	}
	Type Max(){
		return MaxValue(stackA.max(),stackB.max());
	}
	void Enqueue(Type v){
		stackB.push(v);
	}
	Type dequeue(){
		if(stackA.empty()){
			while(!stackB.empty())
				stackA.push(stackB.pop());
		}
		return stackA.pop();
	}
private:
	stack stackA;
	stack stackB;

};


int main(){
	queue q1;
	q1.Enqueue(2);
	q1.Enqueue(3);
	q1.Enqueue(4);
	q1.Enqueue(5);
	q1.Enqueue(1);
	q1.dequeue();
	cout<<q1.Max();
	return 0;
}