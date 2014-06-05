#include <iostream>

using namespace std;

int candidate[3];
int count[3] = {0};

int input[100];
int num = 0;
/************************************************************************/
/* 思路是类似的，同样，每次删除4个不同的ID，不影响“那三个ID在剩余ID中出现仍
然超过1/4”这一事实，因此我们可以每次删除4个不同的ID，直到剩下3个ID为止。具
体编程中怎么体现“删除四个不同ID”这一动作呢？我是这样做的。用candidate[3]记录
三个候选ID，用count[3]记录它们的累积次数，然后遍历整个ID列表，每处理一个ID，若
与candidate[i]中的某一个相同，则count[i]++，若与三个都不同，则说明找到了四个互
不相同的ID，将三个count[i]--，也就相当于“删除了四个不同ID”，若某一个count[i]==0，
则更新之。之前想这个问题的时候一直没想出来，好像也有过类似思路却一直觉得不正确，
这次简单的测试了几组数据，貌似没有问题。如有错误，欢迎指正。
代码如下：                                                                     */
/************************************************************************/

int main()
{
	cout<<"please input"<<endl;
	int t;
	while(cin>>t)
	{
		if (t == -1)
			break;
		input[num++] = t;
	}

	bool flag = false;

	for (int i = 0;i < num;i++)
	{
		flag = false;
		for (int j = 0;j < 3;j++)
		{
			if (count[j] == 0)
			{
				continue;
			}
			if (candidate[j] == input[i])//候选项余存在于当前input中
			{
				count[j]++;
				flag = true;
			}
		}

		if (flag == true)//不做下面处理，即找不到相同的再做一下处理
		{
			continue;
		}

		for (int j = 0;j < 3;j++)
		{
			if (count[j] == 0)
			{
				candidate[j] = input[i];
				count[j]++;
				flag = true;
				break;
			}
		}

		if (flag == true)
		{
			continue;
		}

		for (int j = 0;j < 3;j++)
		{
			count[j]--;
		}

	}

	cout<<count[0]<<" "<<count[1]<<" "<<count[2]<<endl;
	cout<<candidate[0]<<" "<<candidate[1]<<" "<<candidate[2]<<endl;
}