#include <iostream>
#include <vector>
#include <string>
std::vector<std::string> c(10);
std::vector<int> total(10);
void RecursiveSearch(std::vector<int>& number, std::vector<int>& answer, int index, int n)
{
	if (index == n)
	{
		for (int i = 0; i < n; i++)
			printf("%c", c[number[i]][answer[i]]);
		printf("\n");
		return;
	}
	for (answer[index] = 0; 
		answer[index] < total[number[index]];
		answer[index]++)
	{
		RecursiveSearch(number, answer, index + 1, n);
	}
}
void DirectSearch_i(std::vector<int>& number)
{
	int telLength = number.size();
	int resNum = 1;
	for (int i = 0; i < telLength; ++i)
	{
		if (total[number[i]] > 0)
		{
			resNum *= total[number[i]];
		}
	}
	std::vector<std::string> result(resNum, "");
	for (int i = 0; i < telLength; ++i)
	{
		if (0 == total[number[i]])
		{
			continue;
		}
		int loopNum = resNum / total[number[i]];
		int div = 1;
		for (int m = i + 1; m < telLength; ++m)
		{
			if (total[number[m]] > 0)
			{
				div *= total[number[m]];
			}
		}
		int multi = resNum / div;
		int m = -1;
		int n = -1;
		for (int j = 0; j < multi; ++j)
		{
			n++;
			n = n % (total[number[i]]);
			for (int k = 0; k < div; ++k)
			{
				m++;
				result[m].push_back(c[number[i]][n]);
			}
		}
	}
	for (int i = 0; i < resNum; ++i)
	{
		std::cout << result[i] << std::endl;
	}
}
void DirectSearch(std::vector<int>& number, std::vector<int>& answer)
{
	int telLength = number.size();
	while (true)
	{
		for (int i = 0; i < telLength; i++)
			printf("%c", c[number[i]][answer[i]]);
		printf("\n");
		int k = telLength - 1;
		while (k >= 0)
		{
			if (answer[k] < total[number[k]] - 1)
			{
				answer[k]++;
				break;
			}
			else
			{
				answer[k] = 0; k--; 
			}
		}
		if (k < 0)
			break;
	}
}
int main(void)
{
	c[0] = "";            // 0
	c[1] = "";            // 1
	c[2] = "ABC";        // 2
	c[3] = "DEF";        // 3
	c[4] = "GHI";        // 4
	c[5] = "JKL";        // 5
	c[6] = "MNO";        // 6
	c[7] = "PQRS";        // 7
	c[8] = "TUV";        // 8
	c[9] = "WXYZ";        // 9
	total[0] = 0;
	total[1] = 0;
	total[2] = 3;
	total[3] = 3;
	total[4] = 3;
	total[5] = 3;
	total[6] = 3;
	total[7] = 4;
	total[8] = 3;
	total[9] = 4;
	std::vector<int> number;
	//number.push_back(1);
	number.push_back(2);
	number.push_back(3);
	//number.push_back(4);
	//number.push_back(5);
	//number.push_back(6);
	//number.push_back(7);
	int telLength = number.size();
	std::vector<int> answer(telLength, 0); // 开始取的都是数字上的第一个字符
	// Method 1:
	std::cout << "Use method 1:" << std::endl;
	DirectSearch_i(number);
	//Method 2:
	std::cout << "Use method 2:" << std::endl;
	DirectSearch(number, answer);
	// Method 3:
	std::cout << "Use method 3:" << std::endl;
	RecursiveSearch(number, answer, 0, telLength);
	system("pause");
	return 0;
}