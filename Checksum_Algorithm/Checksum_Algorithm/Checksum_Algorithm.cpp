#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class crc_10_10011 {
private:
	char* BitStream;
	char* SEED;
	char  crc[5];
	char  o_str[11];
	int   c[5];  // CRC int array
	int   ch[5]; // Hold previous for next calc
	int   d[10];
	int   o[10];

	char* crc_10_10011::calc() {
		for (int i = 0; i < 4; ++i) {
			c[4 - 1 - i] = SEED[i] - '0';
		}

		for (int i = 0; i < strlen(BitStream); i = i + 10) {
			for (int j = 0; j < 10; j = j + 1) {
				d[j] = BitStream[i + j] - '0';
			}

			for (int k = 0; k < 4; k = k + 1) {
				ch[k] = c[k];
			}
			c[4] = ch[3];
			c[3] = ch[1] ^ ch[2] ^ ch[3] ^ d[9] ^ d[8] ^ d[7] ^ d[5] ^ d[3] ^ d[2] ^ d[9] ^ d[8] ^ d[7] ^ d[5] ^ d[3] ^ d[2] ^ d[9] ^ d[8] ^ d[7] ^ d[5] ^ d[3] ^ d[2] ^ d[9] ^ d[8] ^ d[7] ^ d[5] ^ d[3] ^ d[2] ^ d[9] ^ d[8] ^ d[7] ^ d[5] ^ d[3] ^ d[2] ^ d[9] ^ d[8] ^ d[7] ^ d[5] ^ d[3] ^ d[2] ^ d[9] ^ d[8] ^ d[7] ^ d[5] ^ d[3] ^ d[2] ^ d[9] ^ d[8] ^ d[7] ^ d[5] ^ d[3] ^ d[2] ^ d[9] ^ d[8] ^ d[7] ^ d[5] ^ d[3] ^ d[2] ^ d[9] ^ d[8] ^ d[7] ^ d[5] ^ d[3] ^ d[2];
			c[2] = ch[0] ^ ch[1] ^ ch[2] ^ ch[3] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[4] ^ d[2] ^ d[1] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[4] ^ d[2] ^ d[1] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[4] ^ d[2] ^ d[1] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[4] ^ d[2] ^ d[1] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[4] ^ d[2] ^ d[1] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[4] ^ d[2] ^ d[1] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[4] ^ d[2] ^ d[1] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[4] ^ d[2] ^ d[1] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[4] ^ d[2] ^ d[1] ^ d[9] ^ d[8] ^ d[7] ^ d[6] ^ d[4] ^ d[2] ^ d[1];
			c[1] = ch[0] ^ ch[1] ^ ch[2] ^ d[8] ^ d[7] ^ d[6] ^ d[5] ^ d[3] ^ d[1] ^ d[0] ^ d[8] ^ d[7] ^ d[6] ^ d[5] ^ d[3] ^ d[1] ^ d[0] ^ d[8] ^ d[7] ^ d[6] ^ d[5] ^ d[3] ^ d[1] ^ d[0] ^ d[8] ^ d[7] ^ d[6] ^ d[5] ^ d[3] ^ d[1] ^ d[0] ^ d[8] ^ d[7] ^ d[6] ^ d[5] ^ d[3] ^ d[1] ^ d[0] ^ d[8] ^ d[7] ^ d[6] ^ d[5] ^ d[3] ^ d[1] ^ d[0] ^ d[8] ^ d[7] ^ d[6] ^ d[5] ^ d[3] ^ d[1] ^ d[0] ^ d[8] ^ d[7] ^ d[6] ^ d[5] ^ d[3] ^ d[1] ^ d[0] ^ d[8] ^ d[7] ^ d[6] ^ d[5] ^ d[3] ^ d[1] ^ d[0] ^ d[8] ^ d[7] ^ d[6] ^ d[5] ^ d[3] ^ d[1] ^ d[0];
			c[0] = ch[0] ^ ch[2] ^ ch[3] ^ d[9] ^ d[8] ^ d[6] ^ d[4] ^ d[3] ^ d[0] ^ d[9] ^ d[8] ^ d[6] ^ d[4] ^ d[3] ^ d[0] ^ d[9] ^ d[8] ^ d[6] ^ d[4] ^ d[3] ^ d[0] ^ d[9] ^ d[8] ^ d[6] ^ d[4] ^ d[3] ^ d[0] ^ d[9] ^ d[8] ^ d[6] ^ d[4] ^ d[3] ^ d[0] ^ d[9] ^ d[8] ^ d[6] ^ d[4] ^ d[3] ^ d[0] ^ d[9] ^ d[8] ^ d[6] ^ d[4] ^ d[3] ^ d[0] ^ d[9] ^ d[8] ^ d[6] ^ d[4] ^ d[3] ^ d[0] ^ d[9] ^ d[8] ^ d[6] ^ d[4] ^ d[3] ^ d[0] ^ d[9] ^ d[8] ^ d[6] ^ d[4] ^ d[3] ^ d[0];

			o[9] = ch[0] ^ ch[2] ^ ch[3];
			o[8] = ch[1] ^ ch[3];
			o[7] = ch[0] ^ ch[2];
			o[6] = ch[0] ^ ch[1] ^ ch[3];
			o[5] = ch[1] ^ ch[2];
			o[4] = ch[2] ^ ch[3];
			o[3] = ch[0] ^ ch[3];
			o[2] = ch[1];
			o[1] = ch[2];
			o[0] = ch[4];
		}
		for (int i = 0; i < 4; ++i) {
			crc[4 - 1 - i] = c[i] ? '1' : '0'; // Convert binary to ASCII
		}
		crc[4] = 0;                        // Set string terminator
		for (int i = 0; i < 10; ++i) {
			o_str[10 - 1 - i] = o[i] ? '1' : '0'; // Convert binary to ASCII
		}
		o_str[10] = 0;                        // Set string terminator

		return crc;
	}

public:
	crc_10_10011::crc_10_10011(char * BitStream_in, char*SEED_in = "1010") {
		SEED = SEED_in;
		BitStream = BitStream_in;
		calc();
	}

	crc_10_10011::crc_10_10011(char * BitStream_in) {
		BitStream = BitStream_in;
		calc();
	}

	crc_10_10011::crc_10_10011() {
	}

	crc_10_10011::~crc_10_10011(void) {
	}

	int crc_10_10011::set_data(char * BitStream_in) {
		BitStream = BitStream_in;
		return 0;
	}
	int crc_10_10011::set_seed(char * SEED_in) {
		SEED = SEED_in;
		return 0;
	}
	char* crc_10_10011::get_crc(void) {
		return crc;
	}
	char* crc_10_10011::get_o(void) {
		return o_str;
	}

};

//--------------------------------------------------------------------------
// Test Code

#include <stdio.h>

int main()
{
	char *Data = "0010110011001100";  // Test Data must be in data width boundary
	char *Crc = "";
	char *SEED = "1010";

	crc_10_10011* c_i = new crc_10_10011(Data, SEED);
	Crc = c_i->get_crc();
	printf("CRC of [%s] is [%s] with P=[10011]", Data, Crc);
	return(0);
}