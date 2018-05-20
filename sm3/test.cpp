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
	cout << (0xFFFFFFFF << 31) ;
	return 0;
}
