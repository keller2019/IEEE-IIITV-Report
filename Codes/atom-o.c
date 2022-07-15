#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROUND 510
#define lOOP 200
#define ull unsigned long long
#define ALLONE (0xffffffffffffffffUll)

ull b[90],l[69],c[9],z[lOOP]; 
ull KEY[128],IV[128]; 

//Generate 64 bit random string
ull myrand64(){
    ull temp = (ull) 0;
    int i;
    for (i = 0; i < 64; ++i) {
        temp = ((temp << (ull) 1) | !(drand48() < 0.5));
        
    }
    return temp;
}

void keyload(){
	
	for (int i = 0; i < 128; i++){
		KEY[i] = myrand64();
        		IV[i] = myrand64();
	}
	for (int i = 0; i < 90; i++) b[i] = IV[i];
    
    	for (int i = 0; i < 38; i++) l[i] = IV[i+90];
   
    	for (int i = 38; i < 60; i++) l[i] = ALLONE;
   
}
//filter function
ull h(ull x0, ull x1, ull x2, ull x3, ull x4, ull x5, ull x6, ull x7,ull x8){
	
	ull a = (x0& x1& x2& x7& x8) ^ (x0& x1& x2& x7) ^ (x0& x1& x2& x8) ^ (x0& x1& x2) 
	^ (x0& x1& x3& x7& x8) ^ (x0& x1& x3& x7)^(x0& x1& x4& x7& x8)^(x0& x1& x4& x7)^
	(x0& x1& x4& x8)^(x0& x1& x4)^(x0& x1& x5& x7& x8)^(x0& x1& x5& x7)^(x0& x1& x6& x7& x8)
	^(x0& x1& x6& x8)^(x0& x1& x7& x8)^(x0& x1& x8)^(x0& x2& x3& x7& x8)^(x0& x2& x3& x7)^
	(x0& x2& x3& x8)^(x0& x2& x3)^(x0& x2& x4& x7& x8)^(x0& x2& x4& x8)^(x0& x2& x5& x7& x8)
	^(x0& x2& x5& x7)^(x0& x2& x5& x8)^(x0& x2& x5)^(x0& x2& x6& x7& x8)^(x0& x2& x6& x8)^
	(x0& x2& x7& x8)^(x0& x2& x8)^(x0& x3& x4& x7& x8)^(x0& x3& x4& x7)^(x0& x3& x5& x7& x8)
	^(x0& x3& x5& x7)^(x0& x3& x6& x7& x8)^(x0& x3& x6& x7)^(x0& x3& x8)^(x0& x3)^
	(x0& x4& x5& x7& x8)^(x0& x4& x5& x7)^(x0& x4& x6& x7& x8)^(x0& x4& x6& x8)
	^(x0& x4& x7)^(x0& x4)^(x0& x5& x6& x7& x8)^(x0& x5& x6& x7)^(x0& x5& x7& x8)^(x0& x5& x7)
	^(x0& x6& x7)^(x0& x6& x8)^(x0& x7& x8)^(x1& x2& x3& x7& x8)^(x1& x2& x4& x7& x8)^
	(x1& x2& x4& x8)^(x1& x2& x5& x7& x8)^(x1& x2& x6& x7& x8)^(x1& x2& x6& x8)^(x1& x2& x7)
	^(x1& x2& x8)^(x1& x2)^(x1& x3& x4& x7& x8)^(x1& x3& x5& x7& x8)^(x1& x3& x6& x7& x8)^
	(x1& x3& x7)^(x1& x4& x5& x7& x8)^(x1& x4& x5& x8)^(x1& x4& x6& x7& x8)^(x1& x4& x7)^
	(x1& x4)^(x1& x5& x6& x7& x8)^(x1& x5& x6& x7)^(x1& x5& x7& x8)^(x1& x5& x7)^(x1& x5& x8)
	^(x1& x6& x7)^(x1& x8)^(x1)^(x2& x3& x4& x7& x8)^(x2& x3& x5& x7& x8)^(x2& x3& x6& x7& x8)
	^(x2& x4& x5& x7& x8)^(x2& x4& x5& x8)^(x2& x4& x6& x7& x8)^(x2& x4& x7& x8)^(x2& x4& x8)
	^(x2& x5& x6& x7& x8)^(x2& x5& x6& x8)^(x2& x5& x8)^(x2& x6& x7&x8)^(x2& x6&x8)^(x2& x7&x8)
	^(x2)^(x3& x4& x5& x7& x8)^(x3& x4& x5& x7)^(x3& x4& x6& x7& x8)^(x3& x4& x6& x7)^
	(x3& x5& x6& x7& x8)^(x3& x5& x7& x8)^(x3& x6& x7& x8)^(x3& x6& x7)^(x3& x7)^(x3)^
	(x4& x5& x6& x7& x8)^(x4& x5& x6& x8)^(x4& x6& x7& x8)^(x4& x6& x8)^(x4& x7)^(x5& x7& x8)
	^(x5)^(x6)^(x7& x8)^(x7)^(x8)^(1);
	return a;
}
//intialization
void intialization(){
	int i,cnt=0;
	ull f=0,g=0,z=0;
	
	for(i=0;i<=ROUND;i++){
		for (int j = 0; j < 9; j++) {
            	c[8-j] = (i >> j) & 1;
            	l[60 + j] = c[j];
        		}
        	cnt = l[68] + 2 *l[67] + 4 *l[66] + 8 *l[65] + 16 *l[64] + 32 *l[63] + 64 *l[62];
        	
        	//printf("%d",cnt);
        	
        	f = l[0] ^ l[5] ^ l[12] ^ l[22] ^ l[28] ^ l[37] ^ l[45] ^ l[58];

            g = b[0] ^ b[24] ^ b[49] ^ b[79] ^ b[84] ^ (b[3] & b[59]) ^ (b[10] & b[12])
                ^ (b[15] & b[16])^ (b[25] & b[53]) ^ (b[35] & b[42]) ^ (b[55] & b[58])
                ^ (b[60] & b[74]) ^ (b[20] & b[22] & b[23])^ (b[62] & b[68] & b[72]) 
                ^ (b[77] & b[80] & b[81] & b[83]) ^ l[0] ^ KEY[i % 128];

            z = b[1] ^ b[5] ^ b[11] ^ b[22] ^ b[36] ^ b[53] ^ b[72] ^ b[80] ^ b[84]
                ^ (l[5] & l[16])^ (l[13] & l[15]) ^ (l[30] & l[42]) ^ (c[7] & l[22])
                ^ h(l[7], l[33], l[38], l[50],l[59], c[2], b[85], b[41], b[9]);
          
          for (int j = 0; j < 59; j++) l[j] = l[j + 1];
          
          l[59] = f ^ z;

          for (int j = 0; j < 89; j++) b[j] = b[j + 1];
     
          b[89] = g ^ z ^ l[0]^ KEY[cnt];
    
	i=511;
    	for (int j = 0; j < 9; j++){ 
    	c[8-j] = (i >> j) & 1;
		l[60 + j] = c[j];
	}
    	
     }
}
ull keystream() {
    ull f = 0, g = 0, z = 0;
    int cnt = 0;
    for (int i = 0; i < 200; i++) {
    
        cnt = l[68] + 2 * l[67] + 4 * l[66] + 8 * l[65] + 16 * l[64] + 32 * l[63] + 64 * l[62];
        
        f = l[0] ^ l[5] ^ l[12] ^ l[22] ^ l[28] ^ l[37] ^ l[45] ^ l[58];
        
        g = b[0] ^ b[24] ^ b[49] ^ b[79] ^ b[84] ^ (b[3] & b[59]) ^ (b[10] & b[12])
            ^ (b[15] & b[16])^ (b[25] & b[53]) ^ (b[35] & b[42]) ^ (b[55] & b[58])
            ^ (b[60] & b[74]) ^ (b[20] & b[22] & b[23])^ (b[62] & b[68] & b[72])
            ^ (b[77] & b[80] & b[81] & b[83]) ^ l[0] ^ KEY[cnt]^KEY[i%128];
            
            
        z = b[1] ^ b[5] ^ b[11] ^ b[22] ^ b[36] ^ b[53] ^ b[72] ^ b[80] ^ b[84]
            ^ (l[5] & l[16])^ (l[13] & l[15]) ^ (l[30] & l[42]) ^ (c[7] & l[22])
            ^ h(l[7], l[33], l[38], l[50],l[59], c[2], b[85], b[41], b[9]);
	
        for (int j = 0; j < 68; j++) l[j] = l[j + 1];
        l[68]=f;
        
        for (int j = 0; j < 89; j++) b[j] = b[j + 1];

        b[89] = g ;
        
        return z;
    }
}
int main(){
    
    srand48(time(NULL));
    keyload();
    intialization();
    
    ull z = keystream();
    printf("%llu\n",z);
  
 }
