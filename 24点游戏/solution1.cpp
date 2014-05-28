#include<iostream>
#include<cstdio>
#include<string>
#include<map>
#include<set>
#include<cmath>
#include<ctime>
using namespace std;

//cards[i]的值是通过表达式expr[i]计算而来
//且expr的最后一个运算操作lastop[i]
bool GameRecur(double cards[], string expr[], char lastop[],
	const int cardsNum, const int result)
{
	if(cardsNum == 1)
	{
		if(cards[0] == result)
		{
			//cout<<expr[0]<<endl;
			return true;
		}
		else return false;
	}
	//从已有数中任选两个,计算得到中间结果，并且和剩余的数一起存在cards数组的前
	//cardsNum-1个位置
	map<pair<double,double>,bool> selectedPair;
	for(int i = 0; i<cardsNum; i++)
	{
		for(int k  = i+1; k < cardsNum; k++)
		{
			// 这里的代码没有看懂
			if( selectedPair.find(pair<double, double>(cards[i], cards[k]))
				!= selectedPair.end() || selectedPair.find(pair<double, double>
				(cards[k], cards[i])) != selectedPair.end() )//这里使用find方法，返回的对应的位置，只要对应的位置不是end即说明其中存在，这里的意思即是selectedPair中有相重复的cards
				break;
			else
			{
				selectedPair[pair<double,double>(cards[i], cards[k])] = 1;//1说明其中没有重复的的
				selectedPair[pair<double,double>(cards[k], cards[i])] = 1;
			}
			//上面的代码保证选出的数对不重复
			double a = cards[i], b = cards[k];
			cards[k] = cards[cardsNum-1];
			string expra = expr[i], exprb = expr[k];
			expr[k] = expr[cardsNum-1];
			char lastop_a = lastop[i], lastop_b = lastop[k];
			lastop[k] = lastop[cardsNum-1];

			cards[i] = a + b;
			expr[i] = expra + '+' + exprb;
			lastop[i] = '+';
			if(GameRecur(cards, expr, lastop, cardsNum-1, result))
				return true;

			cards[i] = a - b;
			if('+' == lastop_b || '-' == lastop_b)
				expr[i] = expra + '-' + '(' + exprb + ')';
			else expr[i] = expra + '-' + exprb;
			lastop[i] = '-';
			if(GameRecur(cards, expr, lastop, cardsNum-1, result))
				return true;

			if(a != b)
			{
				cards[i] = b - a;
				if('+' == lastop_a || '-' == lastop_a)
					expr[i] = exprb + '-' + '(' + expra + ')';
				else expr[i] = exprb + '-' + expra;
				lastop[i] = '-';
				if(GameRecur(cards, expr, lastop, cardsNum-1, result))
					return true;
			}

			cards[i] = a * b;
			if('-' == lastop_a || '+' == lastop_a)
				expr[i] = '(' + expra + ')' + '*';
			else expr[i] = expra + '*';
			if('*' == lastop_b || ' ' == lastop_b)
				expr[i] += exprb;
			else expr[i] += '(' + exprb + ')';
			lastop[i] = '*';
			if(GameRecur(cards, expr, lastop, cardsNum-1, result))
				return true;

			if(b != 0)
			{
				cards[i] = a / b;
				if('-' == lastop_a || '+' == lastop_a)
					expr[i] = '(' + expra + ')' + '/';
				else expr[i] = expra + '/';
				if(' ' == lastop_b)
					expr[i] += exprb;
				else expr[i] += '(' + exprb + ')';
				lastop[i] = '/';
				if(GameRecur(cards, expr, lastop, cardsNum-1, result))
					return true;
			}

			if(a != 0 && a!= b)
			{
				cards[i] = b / a;
				if('-' == lastop_b || '+' == lastop_b)
					expr[i] = '(' + exprb + ')' + '/';
				else expr[i] = exprb + '/';
				if(' ' == lastop_a)
					expr[i] += expra;
				else expr[i] += '(' + expra + ')';
				lastop[i] = '/';
				if(GameRecur(cards, expr, lastop, cardsNum-1, result))
					return true;
			}

			//把选出来的两个数放回原位
			cards[i] = a;
			cards[k] = b;
			expr[i] = expra;
			expr[k] = exprb;
			lastop[i] = lastop_a;
			lastop[k] = lastop_b;
		}
	}
	return false;
}

//cards 输入的牌
//cardsNum 牌的数目
//result 想要运算得到的结果
const int cardsNum=4;
string PointGame(int cards[], const int result)
{
	string expr[cardsNum];
	char lastop[cardsNum];
	double cardsCopy[cardsNum];
	for(int i = 0; i < cardsNum; i++)
	{
		char buf[30];
		sprintf(buf, "%d", cards[i]);
		expr[i] = buf;
		lastop[i] = ' ';//表示cardsCopy[i]是不经过任何运算的原始数据
		cardsCopy[i] = cards[i];
	}
	if(GameRecur(cardsCopy, expr, lastop, cardsNum, result))
		return expr[0];
	else return "-1";
}


int main(){
	int cards[4]={11,8,3,5};
	cout<<PointGame(cards,24);
}