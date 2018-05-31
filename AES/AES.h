#ifndef AES_H

#include<iostream>
#include<windows.h>
#include<cstdlib>

using namespace std;

/*
reference: 
https://nvlpubs.nist.gov/nistpubs/fips/nist.fips.197.pdf
*/
 
class AES
{
private:
	int Nb, Nk, Nr; // number of word of the key    number of round
	
	unsigned int * w;   // key expansion
	unsigned int rol(unsigned int X, int n);
	unsigned int rot_word(unsigned int w); // Ñ­»·×óÒÆ8Î» 
	unsigned int sub_word(unsigned int w);
	unsigned int rcon(unsigned int i);
	uint8_t gmult(uint8_t a, uint8_t b);
	void coef_mult(uint8_t *a, uint8_t *b, uint8_t *d);
public:
	AES(int key_length);
	//void init();
	bool get_rand_key(UINT* RandomArray,UINT size);
	
	void key_expansion(unsigned int * key); //, unsigned int * w);
	
	void AddRoundKey(uint8_t * state, uint8_t begin);
	void SubBytes(uint8_t * state);
	void ShiftRows(uint8_t * state);
	void MixColumns(uint8_t * state);
	
	void cipher(uint8_t * in, uint8_t * out); //, unsigned int * w);
	void print_hex(unsigned int * message, int length);
	void print_hex(uint8_t * message, int length);
	
	~AES();
};
#endif 
