#include"sm3.h"
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cstdlib>
using namespace std;

const unsigned int IV[8] = {0x7380166f, 0x4914b2b9, 0x172442d7, 0xda8a0600, 0xa96f30bc, 0x163138aa, 0xe38dee4d, 0xb0fb0e4e};

SM3::SM3()
{
	for(int i = 0; i < 16; ++i) T[i] = 0x79cc4519;
	for(int i = 16; i < 64; ++i) T[i] = 0x7a879d8a;
}
inline unsigned int SM3::rol(unsigned int X, int n)
{
	unsigned int res = X << n;
	res |= (X >> (32 - n));
	return res;
}

inline unsigned int SM3::FF(unsigned int X, unsigned int Y, unsigned int Z, int j)
{
	/*if(j >= 0 && j <= 15)
	{
		return X ^ Y ^ Z;
	}
	else if(j >= 16 && j <= 63)
	{
		return (X & Y) | (X & Z) | (Y & Z);
	}*/
	
	if(j >= 0)
	{
		if(j < 16) return X ^ Y ^ Z;
		else if(j < 64) return (X & Y) | (X & Z) | (Y & Z);
	} 
	return 0; // 有问题 
}

inline unsigned int SM3::GG(unsigned int X, unsigned int Y, unsigned int Z, int j)
{
	/*if(j >= 0 && j <= 15)
	{
		return X ^ Y ^ Z;
	}
	else if(j >= 16 && j <= 63)
	{
		return (X & Y) | ((~X) & Z);
	}*/
	if(j >= 0)
	{
		if(j < 16) return X ^ Y ^ Z;
		else if(j < 64) return (X & Y) | ((~X) & Z);
	} 
	return 0; // 有问题 
}

inline unsigned int SM3::P0(unsigned int X)
{
	return (X ^ (rol(X, 9)) ^ (rol(X, 17)));
}

inline unsigned int SM3::P1(unsigned int X)
{
	return (X ^ (rol(X, 15)) ^ (rol(X, 23)));
}

unsigned int * SM3::fill(unsigned int * message, ULL length) // message 的长度  /bits
{
	ULL l = length;
	int k = 448 - l % 512;
	
	if(k < 0) k += 512;
	
	//k = k / 8;
	//
	filled_len = (l + k + 64) / 32; 
	unsigned int * fill_message = new unsigned int[filled_len];
	
//	memset(fill_message, 0, filled_len * sizeof(unsigned int));
	memset(fill_message, 0, filled_len * sizeof(unsigned int));
	//for(int i = 0; i < filled_len; ++i) fill_message[i] = 0;
	
	ULL now = 0;
	int current_bit;
	
	int bias = length % 32;
	now = length / 32;
	
	int cnt;
	if(bias == 0)
	{
		cnt = now; 
	}
	else
	{
		cnt = now + 1; 
	}
	
	
	current_bit = 24 - bias;
/*	if(bias == 0)
	{
		now = cnt;
		current_bit = 24;
	}
	else
	{
		now = length / 32;
		current_bit = 24 - bias;
	}*/
	
	for(ULL i = 0; i < cnt; ++i)
	{
		fill_message[i] = message[i];
	}
	
	if(bias != 0)
	{
		fill_message[now] &= (0xFFFFFFFF << (32 - bias));
	}
    
	//now = length;
	
	unsigned int tmp = 128; // 1 << 7
	
	fill_message[now] |= (tmp << current_bit);
	current_bit -= 8;
	if(current_bit < 0)
	{
		now ++;
		current_bit = 24;
	}
	
	tmp = 0;
	for(int i = 0; i < k / 8 - 1; ++i)
	{
		fill_message[now] |= (tmp << current_bit);
		current_bit -= 8;
		if(current_bit < 0)
		{
			now ++;
			current_bit = 24;
		}
	} 
	
	fill_message[filled_len - 1] = (l & 0xFFFFFFFF);
	fill_message[filled_len - 2] = ((l >> 32) & 0xFFFFFFFF);
	
	return fill_message;
}

unsigned int * SM3::fill(unsigned char *message) // 填充  
{
	ULL length = strlen((char *)message);
	
	ULL l = 8 * length;
	int k = 448 - l % 512;
	
	if(k < 0) k += 512;
	
	//k = k / 8;
	//
	filled_len = (l + k + 64) / 32; 
	unsigned int * fill_message = new unsigned int[filled_len];
	
//	memset(fill_message, 0, filled_len * sizeof(unsigned int));
	memset(fill_message, 0, filled_len * sizeof(unsigned int));
	//for(int i = 0; i < filled_len; ++i) fill_message[i] = 0;
	
	ULL now = 0;
	int current_bit = 24;
	
	for(ULL i = 0; i < length; ++i)
	{
		fill_message[now] |= (message[i] << current_bit);
		current_bit -= 8;
		if(current_bit < 0)
		{
			now ++;
			current_bit = 24;
		}
	}
	
	unsigned int tmp = 128; // 1 << 7
	
	fill_message[now] |= (tmp << current_bit);
	current_bit -= 8;
	if(current_bit < 0)
	{
		now ++;
		current_bit = 24;
	}
	
	tmp = 0;
	for(int i = 0; i < k / 8 - 1; ++i)
	{
		fill_message[now] |= (tmp << current_bit);
		current_bit -= 8;
		if(current_bit < 0)
		{
			now ++;
			current_bit = 24;
		}
	} 
	
	fill_message[filled_len - 1] = (l & 0xFFFFFFFF);
	fill_message[filled_len - 2] = ((l >> 32) & 0xFFFFFFFF);
	
	return fill_message;
}


inline void SM3::CF(unsigned int * V, unsigned int * message, ULL num)
{
	 
	for(int i = 0; i < 16; ++i)
	{
		W[i] = message[num ++];
	}
	
	for(int i = 16; i <= 67; ++i)
	{
		W[i] = P1(W[i - 16] ^ W[i - 9] ^ rol(W[i - 3], 15)) ^ rol(W[i - 13], 7) ^ W[i - 6];
	}
	
	for(int i = 0; i < 64; ++i)
	{
		W_[i] = W[i] ^ W[i + 4];
	}
	
	//cout << "W is " << endl;
//	print_hex(W, 68);
	
	//cout << "W_ is " << endl;
	//print_hex(W_, 64);
	
	unsigned int A = V[0];
	unsigned int B = V[1];
	unsigned int C = V[2];
	unsigned int D = V[3];
	unsigned int E = V[4];
	unsigned int F = V[5];
	unsigned int G = V[6];
	unsigned int H = V[7];
	
	for(int i = 0; i < 64; ++i)
	{
		unsigned int tmp = rol(A, 12);
		unsigned int SS1 = rol(tmp + E + rol(T[i], i), 7);
		unsigned int SS2 = SS1 ^ tmp;
		
		unsigned int TT1 = FF(A, B, C, i) + D + SS2 + W_[i];
		unsigned int TT2 = GG(E, F, G, i) + H + SS1 + W[i];
		
		D = C;
		C = rol(B, 9);
		B = A;
		
		A = TT1;
		H = G;
		G = rol(F, 19);
		F = E;
		E = P0(TT2);
	}
	
	V[0] ^= A;
	V[1] ^= B;
	V[2] ^= C;
	V[3] ^= D;
	V[4] ^= E;
	V[5] ^= F;
	V[6] ^= G;
	V[7] ^= H;
	
}

void SM3::iter(unsigned int * message)
{
	ULL n = filled_len / 16;
	
	
	for(int i = 0; i < 8; ++i) V[i] = IV[i];
	for(int i = 0; i < n; ++i)
	{
		CF(V, message, i * 16);
	}
	
//	return V;
}

void SM3::calculate_sm3(unsigned char * message)
{
	unsigned int * filled_message = fill(message);
		
	iter(filled_message);
	
	
	delete [] filled_message;
//	print_hex(V, 8);	
}

void SM3::calculate_sm3(unsigned int * message, ULL length)
{
	unsigned int * filled_message = fill(message, length);
		
	iter(filled_message);
	
	delete [] filled_message;
}

void SM3::print_str(string &s)
{
	string ret;
    for (ULL i = 0; i != s.size(); ++i)
    {
        char hex[5];
        sprintf(hex, "%.2x", (unsigned char)s[i]);
        ret += hex;
        
        if(i % 4 == 3) ret += " ";
    }
    //return ret;
    
    cout << ret << endl;
}

void SM3::print_hex(unsigned int * message, ULL length)
{
	for(ULL i = 0; i < length; ++i)
	{
		printf("%.8x ", message[i]);
	}
	printf("\n");
}
