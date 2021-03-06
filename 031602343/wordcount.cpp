#include "pch.h"
#include <iostream>
#include <fstream>
#include <cassert>
#include <string>
#include <regex>
#include <vector>
#include <map>
using  namespace std;

int charcount(string filename)
{

	int count1 = 0;

	ifstream infile;
	infile.open(filename.data());   //将文件流对象与文件连接起来 
	assert(infile.is_open());   //若失败,则输出错误消息,并终止程序运行 

	char c;


	infile >> noskipws;//逐个字符读入（包括空格和回车）
	while (infile >> c)
	{

		if (c >= 0 && c <= 255)
		{
			count1++;
		}
	}

	infile.close();//关闭文件输入流 
	return count1;

}

int linecount(string filename)//逐行读入
{
	int count2 = 0;
	string line;
	ifstream file(filename);//强制读取文件内容
	while (getline(file, line))
	{
		int l = line.length();
		for (int i = 0; i < l; i++)
		{
			if (line[i] != 13 && line[i] != 10 && line[i] != 32)
			{
				count2++;
				break;
			}//查找本行中是否有除了空格、换行、回车外的字符
		}
	}
	file.clear();
	file.seekg(0);
	return count2;
}

bool findword(pair<string, int> elem1, pair<string, int> elem2)
{
	return elem1.second > elem2.second;
}
void frequency(string  filename)
{
	ofstream output("1.txt", ios::app);
	

	string s;
	map<string, int> find;
	regex WordPatternreg("^[a-z]{4}[a-z0-9]*");//我们要匹配的单词的正则式
	ifstream ifs(filename);//强制读取文件内容
	while (ifs >> s)
	{
		int l = s.length();//
		for (int i = 0; i < l; i++)
		{
			if (s[i] >= 65 && s[i] <= 90)
			{
				s[i] = s[i] + 32;
			}
		}//将大写转换成小写
		const std::sregex_token_iterator end;
		for (sregex_token_iterator wordIter(s.begin(), s.end(), WordPatternreg); wordIter != end; wordIter++)
		{//在一行文本中逐个找出单词
																															 //cout<<*wordIter<<endl;//每个单词
			find[*wordIter]++;//单词计数
		}
	}
	ifs.clear();
	ifs.seekg(0);

	vector<pair<string, int>> ci;
	for (map<string, int>::iterator iter = find.begin(); iter != find.end(); iter++)
	{
		ci.push_back(pair<string, int>(iter->first, iter->second));
	}
	sort(ci.begin(), ci.end(), findword);
	int size = 10;

	int count3 = ci.size();//统计数组里单词的个数
	

	if (output.is_open())
	{

		output << "word:" << count3 << endl;

		if (ci.size() < 10)
		{
			size = ci.size();
		}

		vector<pair<string, int>>::iterator vit;

		for (vit = ci.begin(); vit != ci.begin() + size; vit++)
		{
			output << "<" << vit->first << ">:" << " " << vit->second << endl;
		}
	}
	output.close();
}

int main(int argc, const char* argv[])
{
	int countword(string filename);
	int i;
	for (i = 1; i < argc; i++)
	{
		string filename = argv[i];
		int a = charcount(filename);
		int b = linecount(filename);
		


		ofstream output("1.txt");
		if (output.is_open())
		{
			output << "characters: " << a << endl;
			output << "line:" << b << endl;
		}
		output.close();
		frequency(filename);
        
	}
	return 0;
}

