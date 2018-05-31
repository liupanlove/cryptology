#include"sm3.h"
#include<cstdio>
#include<fstream>
#include<ctime>
#include<sys/time.h>
using namespace std;

#define MAXN 200000000

unsigned char message[MAXN];

int ts, te;
struct timeval tv;

#define TIME_TICK_START gettimeofday( &tv, NULL ); ts = tv.tv_sec * 100000 + tv.tv_usec / 10;
#define TIME_TICK_END gettimeofday( &tv, NULL ); te = tv.tv_sec * 100000 + tv.tv_usec / 10;
#define TIME_TICK_PRINT(T) printf("%s RESULT: %lld (0.01MS)\r\n", (#T), te - ts );

int main()
{
	SM3 sm3;
		
	
	
	ifstream fin("test.txt");
	
	unsigned long long cnt = 0;
	while(!fin.eof())
	{
		fin >> message[cnt];
		cnt ++;
	}
	
	
	TIME_TICK_START
	sm3.calculate_sm3(message);
	
	sm3.print_hex(sm3.V, 8);
	
	TIME_TICK_END
	TIME_TICK_PRINT(END);
	
	fin.close();
	return 0;
}
