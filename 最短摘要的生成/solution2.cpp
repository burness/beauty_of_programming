#include<iostream>
#include<string>
#include<map>
#include<deque>
using namespace std;

void find_min_len_abstract(string str[], string keyword[], int len_str, int len_keyword) {
	// 初始化map 
	map<string,int> record;
	for(int i=0; i<len_keyword; i++) {
		record[keyword[i]] = 0;
	}
	// 匹配过程
	deque<int> store; // 存储的是str中关键词的对应下标 
	int min_len = 0;
	int min_index_first = -1;
	int min_index_last = -1;
	int find_key_num = 0;
	int index = 0;
	while(find_key_num < len_keyword && index < len_str) {
		if(record.find(str[index]) == record.end()) { // str[index]不是关键字 
			index++;
		}
		else { // str[index]是关键字 
			if(record[str[index]] == 0) // 第一次找到这个关键字
				find_key_num ++;
			record[str[index]] = record[str[index]] + 1; // 对应关键词计数加1
			store.push_back(index); 
			index++;
		}
	}
	// find_key_num表示已经在str中找到的数目，len_keyword 表示关键词的长度
	if(find_key_num < len_keyword) { // 一个满足的摘要都没找到 
		cout << "not abstract found " << endl;
	}

	else { // 找到一个了，试着找找更好的 
		min_len = store.back()- store.front() + 1;   
		min_index_first = store.front();
		min_index_last = store.back();
		// 第一个摘要 
		cout << "第一个摘要" << endl; 
		cout << "min len: " << min_len << endl;
		for(int i=min_index_first; i<=min_index_last; i++)
			cout << str[i] << " ";
		cout << endl; 
		cout << "---------------------------------------------" << endl;
		string need_key;
		bool already_found = true;
		while(true) {   
			if(already_found == true) { // 刚好找到一个新摘要 
				string first_key = str[store.front()];
				record[first_key]--; // 减少当前最前面的关键词 
				store.pop_front(); // 关键词出队 
				if(record[first_key] == 0) { // 如果该关键词没了 
					already_found = false;
					need_key = first_key; // 记录需要寻找的关键词 
				}               
				else { // 少了词语，但是还包含所有关键词，说明这是一个更短的摘要 
					min_len--;
					min_index_first ++;
					cout << "更短的摘要" << endl;
					cout << "min len: " << min_len << endl;
					for(int i=min_index_first; i<=min_index_last; i++)
						cout << str[i] << " ";
					cout << endl; 
					cout << "---------------------------------------------" << endl;
				}
			}
			else { // 需要向后面找满足条件的关键词 
				if(index >= len_str) { // 不可能找到需要的关键词了 
					break;
				}
				else if(record.find(str[index]) == record.end()) { // 不是关键词 
					index++;
				}
				else { // 是关键词 
					record[str[index]] = record[str[index]]+1;
					store.push_back(index); 
					if(str[index] == need_key) { // 正好还是需要找到的关键词
						already_found = true;
						if((store.back()-store.front() + 1) < min_len) { // 新的摘要更短 
							min_len = store.back() - store.front() + 1;
							min_index_first = store.front();
							min_index_last = store.back();
							// 更短的摘要
							cout << "更短的摘要" << endl;
							cout << "min len: " << min_len << endl;
							for(int i=min_index_first; i<=min_index_last; i++)
								cout << str[i] << " ";
							cout << endl; 
							cout << "---------------------------------------------" << endl;
						}
						else {
							cout << "并非更短的摘要" << endl;
							cout << "min len: " << store.back() - store.front() + 1 << endl;
							for(int i=store.front(); i<=store.back(); i++)
								cout << str[i] << " ";
							cout << endl; 
							cout << "---------------------------------------------" << endl;
						}
					}
					index++; 
				} // else
			} // else
		} // while
	} // else
	// 输出结果
}

int main() {  
	// string keyword[] = { "微软", "计算机", "亚洲", "中国"};
	string keyword[] = { "微软", "计算机", "亚洲"};
	string str[] = { 
		"微软","亚洲","研究院","成立","于","1998","年","，","我们","的","使命",
		"是","使","未来","的","计算机","能够","看","、","听","、","学","，",
		"能","用","自然语言","与","人类","进行","交流","。","在","此","基础","上",
		"，","微软","亚洲","研究院","还","将","促进","计算机","在","亚太","地区",
		"的","普及","，","改善","亚太","用户","的","计算","体验","。","”"
	};
	int len_keyword = sizeof(keyword)/sizeof(string);
	int len_str = sizeof(str)/sizeof(string);
	find_min_len_abstract(str, keyword, len_str, len_keyword);

	system("PAUSE");
	return 0;
}