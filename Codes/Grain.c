#include<stdio.h>
#include<stdlib.h>
#include <string.h>
unsigned int s[80];
unsigned int b[80];

void lfsr() {
	int y = (s[62] ^ s[51] ^ s[38] ^ s[23] ^ s[13] ^ s[0]);
	int i;
		for(i=0; i<79; i++) {
				s[i] = s[i+1];
					}
	s[79] = y;
	}
void nfsr() {
	int y = (s[0] ^ b[62] ^ b[60] ^ b[52] ^ b[45] ^ b[37] ^ b[33] ^ b[28] ^ b[21] ^ b[14] ^ b[9] ^ b[0] ^ (b[63]&b[60]) ^ (b[37]&b[33]) ^ 
		(b[15]&b[9]) ^ (b[60]&b[52]&b[45]) ^ (b[33]&b[28]&b[21]) ^ (b[63]&b[45]&b[28]&b[9]) ^ (b[60]&b[52]&b[37]&b[33]) ^ (b[63]&b[60]&b[21]&b[15]) ^
			(b[63]&b[60]&b[52]&b[45]&b[37]) ^ (b[33]&b[28]&b[21]&b[15]&b[9]) ^ (b[52]&b[45]&b[37]&b[33]&b[28]&b[21]));
	int i;
		for(i=0; i<79; i++) {
				b[i] = b[i+1];
					}
	b[79] = y;
	}
int zstream() {
	int x0 = s[3], x1 = s[25], x2 = s[46], x3 = s[64], x4 = b[63];
		int h = (x1 ^ x4 ^ x0&x3 ^ x2&x3 ^ x3&x4 ^ 
					x0&x1&x2 ^ x0&x2&x3 ^ x0&x2&x4 ^ x1&x2&x4 ^ x2&x3&x4);
	int z = b[1] ^ b[2] ^ b[4] ^ b[10] ^ b[31] ^ b[43] ^ b[56] ^ h;
	nfsr();
		lfsr();
	return z;
	}
void initialize(int *key, int *iv) {
	int i, j;
		for(i=0; i<8; i++) {
				for(j=0; j<8; j++) {
			b[i*8+j] = ((key[i]>>j) & 1);
						s[i*8+j] = ((iv[i]>>j) & 1);
								}
									}
	for(i=8; i<10; i++) {
			for(j=0; j<8; j++) {
						b[i*8+j] = ((key[i]>>j) & 1);
									s[i*8+j] = 1;
											}
												}
	int k;
		while(k<160) {
				int z = zstream();
						s[79] ^= z;
								b[79] ^= z;
										k++;
											}
}

void keystreamGenerate(int *keystream, int msglen) {
	int i,j;
		for (i=0; i<msglen; ++i) {
				keystream[i]=0;
						for (j=0; j<8; ++j) {
									int z = zstream();
												keystream[i] |= (z<<j);
														}
															}
	printf("Keystream: ");
		for(i=0; i<msglen; i++) {
				printf("%02x", keystream[i]);
					}
					}
void encrypt(int *msg, int *keystream, int msglen, int *encryptedmsg) {
	int i, j, k;
	for(i=0; i<msglen; i++) {
			k=0;
					for(j=0; j<8; j++) {
								k |= (keystream[i]<<j);
										}
												encryptedmsg[i] = msg[i]^k;
													}
	printf("\nEncrypted msg: ");
		for(i=0; i<msglen; i++) {
				printf("%02x", encryptedmsg[i]);
					}
					}
void decrypt(int *encryptedmsg, int *keystream, int msglen) {
	int i, j, k;
		int decryptedmsg[msglen];
			for(i=0; i<msglen; i++) {
					k=0;
							for(j=0; j<8; j++) {
										k |= (keystream[i]<<j);
												}
														decryptedmsg[i] = encryptedmsg[i]^k;
															}
	printf("\nDecrypted msg: ");
		for(i=0; i<msglen; i++) {
				printf("%c", decryptedmsg[i]);
					}
					}
int main() {
	char msg[] = "Grain-v1 encryption!";
		int msglen = strlen(msg), i;
	int plainText[msglen];
		for(i=0; i<msglen; i++) {
				plainText[i] = (int) msg[i];
					}
	int key[10] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
		int iv[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
			initialize(key, iv);
	int keystream[msglen];
		keystreamGenerate(keystream, msglen);
	int encryptedmsg[msglen];
		encrypt(plainText, keystream, msglen, encryptedmsg);
	decrypt(encryptedmsg, keystream, msglen);
	return 0;
	}