#include"sm3.h"
#include<cstdio>
#include<fstream>
#include<ctime>
#include<sys/time.h>
using namespace std;

#define MAXN 100000000

unsigned char message1[MAXN];

int ts, te;
struct timeval tv;
#define TIME_TICK_START gettimeofday( &tv, NULL ); ts = tv.tv_sec * 100000 + tv.tv_usec / 10;
#define TIME_TICK_END gettimeofday( &tv, NULL ); te = tv.tv_sec * 100000 + tv.tv_usec / 10;
#define TIME_TICK_PRINT(T) printf("%s RESULT: %lld (0.01MS)\r\n", (#T), te - ts );

int main()
{
	SM3 sm3;
	
 	 
	
	/*ifstream fin("test.txt");
	
	fin >> message;*/
	cin >> message1;
	///cout << strlen((char *)message) << endl;
	
	unsigned int message[20];
	
	for(int i = 0; i < 16; ++i)
	{
		message[i] = 0x61626364;
	}
	
	
	//TIME_TICK_START
	cout << "haipa" << endl;
	unsigned int * filled_message = sm3.fill(message, 16 * 32);
	
	cout << "haipa" << endl;
	sm3.print_hex(filled_message, sm3.filled_len);
	
	cout << "haipa" << endl;
	sm3.iter(filled_message);
	
	cout << "hash value is " << endl;
	sm3.print_hex(sm3.V, 8);
	
	
	
	sm3.calculate_sm3(message1);
	
	///TIME_TICK_END
	//TIME_TICK_PRINT(END);
	return 0;
}
