#include <stdio.h>
#include <string.h>

#define BASE58_ENCODE_BASE 0
#define BASE58_DECODE_BASE 0

void print_array(unsigned char* arr, int len)
{
	int i = 0;
	for (i=0; i<len; ++i){		printf("%02X",arr[i]);	}
	printf("\n");
}

static unsigned char alphabet[] = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz"; // 0oIl

int base58Encode(const char* input,const unsigned int inLen,unsigned char *output,unsigned int outLen)
{
	int i,j,tmp;
	memset(output,0,outLen);
	for(i=0;i<inLen;i++)
	{
		unsigned int c = input[i] & (0xff) ;
		for(j=outLen-1;j>=0;j--)
		{
			tmp = output[j] * 256 + c;
			c = tmp/58;
			output[j] = tmp%58;
		}
	}
	for(j=0; j<outLen; ++j)	{		output[j] = alphabet[output[j]];	}
	return BASE58_ENCODE_BASE;
}

int base58Decode(const char* addr,const unsigned int addrLen,unsigned char *buf,unsigned int bufLen)
{
	int i,j;
	unsigned int tmp;
	memset(buf,0,bufLen);
	for(i=0; i<addrLen; i++)
	{
		unsigned int c = addr[i];

	 if (addr[i] < 58){ c -= 49;} // номера		
    else if (addr[i] < 73){ c -= 56;} // A-H
    else if (addr[i] < 79){ c -= 57;} // J-N
    else if (addr[i] < 91){ c -= 58;} // P-Z
    else if (addr[i] <108){ c -= 64;} // a-k
    else                  { c -= 65;} // m-z

		for(j=bufLen-1;j>=0;j--)
		{
			   tmp = buf[j] * 58 + c;
			     c = (tmp & (~0xff)) >> 8;
			buf[j] =  tmp & ( 0xff);
		}
	}
	return BASE58_DECODE_BASE;
}

int main()
{
  char addr[]="113YAvwi1V9WV9GEykK6XQ1UypmFPhVyh1"; 

	const int addrLen = 34;
	const int bufLen = 25;
	char buf[bufLen];
	char addr2[addrLen];  
	memset(buf,0,bufLen);	  

  print_array(addr,addrLen);	
  base58Decode(addr, addrLen, buf, bufLen);	
  
  print_array(buf,bufLen);  
  base58Encode(buf, bufLen, addr2, addrLen);	
    
  print_array(addr2,addrLen); // backtest

	return 0;
}  
