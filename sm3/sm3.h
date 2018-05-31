#ifndef SM3_H
#define SM3_H

#include<iostream>
#include<cstring>
using namespace std;

typedef unsigned long long ULL;

class SM3
{
private:
	//string num2str();
	unsigned int P0(unsigned int X);
	unsigned int P1(unsigned int X);
	unsigned int rol(unsigned int X, int n);  // 循环左移 
	unsigned int FF(unsigned int X, unsigned int Y, unsigned int Z, int j);
	unsigned int GG(unsigned int X, unsigned int Y, unsigned int Z, int j);
public:
	SM3();
	ULL filled_len;
	unsigned int W[68];
	unsigned int W_[64];
	unsigned int V[8];
	unsigned int T[64];
	
	unsigned int * fill(unsigned char * str);  // 对于char*的消息填充 
	unsigned int * fill(unsigned int * message, ULL length); //  对于十六进制的消息进行填充 
	void iter(unsigned int * message);  // 迭代 
	
	void CF(unsigned int * v, unsigned int * message, ULL num);
	void print_str(string &s);
	void print_hex(unsigned int * message, ULL length);  // 输出调试信息 
	
	void calculate_sm3(unsigned int * message, ULL length);  // 计算 sm3，输入为十六进制 
	
	void calculate_sm3(unsigned char * message);  // 计算 sm3  ， 输入为char*
};


#endif
