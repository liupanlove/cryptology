#include<iostream>
#include"sm3.h"
using namespace std;

#define MAXN 1000000
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
	ULL len; // Åö×²µÄ³¤¶È 
	
	cout << "input the len: ";
	cin >> len;
	unsigned int message[10];
	
	for(int i = 0; i < 10; ++i) message[i] = 0;
	
	
	SM3 sm3_1;
	sm3_1.calculate_sm3(message, len);
	SM3 sm3_2;
	
	sm3_2.calculate_sm3(message, len);
	sm3_2.calculate_sm3(sm3_2.V, len);
	
	
	ULL cnt = 0;
	
	while(!isequal(sm3_1.V, sm3_2.V, len))
	{
		sm3_1.calculate_sm3(sm3_1.V, len);
		
		sm3_2.calculate_sm3(sm3_2.V, len);
		sm3_2.calculate_sm3(sm3_2.V, len);
		
		cnt ++;
		if(cnt % MAXN == 0)
		{
			
			cout << cnt << endl;
		}
	}
	
	unsigned int tmp1[8];
	unsigned int tmp2[8];
	
	
	sm3_1.calculate_sm3(message, len);
	sm3_2.calculate_sm3(sm3_2.V, len);
	
	
	
	while(!isequal(sm3_1.V, sm3_2.V, len))
	{
		for(int i = 0; i < 8; ++i)
		{
			tmp1[i] = sm3_1.V[i];
			tmp2[i] = sm3_2.V[i];
		}
		
		sm3_1.calculate_sm3(sm3_1.V, len);
		
		sm3_2.calculate_sm3(sm3_2.V, len);
		
		cnt ++;
		if(cnt % MAXN == 0)
		{
			
			cout << cnt << endl;
		}
	}
	
	
	sm3_1.calculate_sm3(tmp1, len);
	sm3_2.calculate_sm3(tmp2, len);
	sm3_1.print_hex(tmp1, 8);
	sm3_2.print_hex(tmp2, 8);
	
	sm3_1.print_hex(sm3_1.V, 8);
	sm3_2.print_hex(sm3_2.V, 8);

		
	return 0;
}
