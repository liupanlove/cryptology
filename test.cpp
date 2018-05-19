#include<iostream>
#include<fstream>
#include<sstream>
#include<cstdlib>
#include<cstring>
using namespace std;

typedef unsigned long long ULL;
bool isequal(unsigned int * V1, unsigned int * V2, ULL len)
{
	ULL n = len / 32;
	int m = len % 32;
	
	for(ULL i = 0; i < n; ++i)
	{
		if(V1[i] != V2[i])  return false;
	}
	
	if(m != 0)
	{
		int tmp = 32 - m;
		unsigned int tmp1 = V1[n] >> tmp;
		unsigned int tmp2 = V2[n] >> tmp;
		
		return (tmp1 == tmp2);
	}
	return true;
}
int main()
{
	unsigned int V1[10];
	V1[0] = 1;
	unsigned int V2[10];
	V2[0] = 0;
	
	cout << isequal(V1, V2, 32) << endl;
	return 0;
}
