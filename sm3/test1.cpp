#include<iostream>
#include<fstream> 
#include<ctime>
#include<cstdio>
#include<cstdlib>
using namespace std;

int main()
{
	ofstream fout("test.txt");
	cout << (int)'A' << endl;
	cout << (int)'z' << endl;
	for(int i = 0; i < 104857600; ++i)
		fout << (char)(rand() % 58 + 65);
	fout.close();
	return 0;
} 
