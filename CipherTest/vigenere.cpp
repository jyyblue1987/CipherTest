#include <stdio.h>

#define MAX_LEN 512
#define COL_NUM 80

int readData(char *path, char *data, bool padding) 
{
	int cnt = 0;
	char c = 0;
	FILE *file = fopen(path, "r");
	if( file ) 
	{
		while ((c = getc(file)) != EOF)
		{
			if( 'a' <= c && c <= 'z' || 'A' <= c && c <= 'Z')
			{
				if( 'A' <= c && c <= 'Z' )
					c = c - 'A' + 'a';

				if( cnt >= MAX_LEN )
					break;

				data[cnt] = c;
				cnt++;
			}			
		}

		fclose(file);

		if( padding == true )
		{
			for(; cnt < MAX_LEN; cnt++)
				data[cnt] = 'x';

			data[MAX_LEN] = NULL;
			return MAX_LEN;
		}
		else
		{
			data[cnt] = NULL;
			return cnt;
		}
	}
}

void printData(char *data) 
{
	int i = 0;
	while(true)
	{
		char c = data[i];
		if( c == NULL )
			break;

		if( i > 0 && i % COL_NUM == 0 )
			printf("\n");

		printf("%c", c);

		i++;
	}
}

void cipherText(char *key, char *plain, char *cipher, int key_len, int plain_len)
{
	int i = 0, j = 0;
	for(i = 0; i < plain_len; i++, j++)
	{
		if( j >= key_len )
			j = 0;
		char c = (plain[i] + key[j] - 'a');
		if( c > 'z' )
			c = c - 'z' - 1 + 'a';
		cipher[i] = c;
	}

	cipher[i] = NULL;
}

int main(int argc,char** argv)
{
	if( argc < 3 )
	{
		printf("Param is invalid");
		return -1;
	}

	char key_data[MAX_LEN + 1];
	char plain_data[MAX_LEN + 1];
	char cipher_data[MAX_LEN + 1];

	char *key = argv[1];
	char *content = argv[2];

	// read key file
	int key_len = readData(key, key_data, false);

	// read plain file
	int plain_len = readData(content, plain_data, true);
		
	// print key data
	printf("\n\nVigenere Key:\n\n");
	printData(key_data);

	// print plain data
	printf("\n\n\nPlaintext:\n\n");
	printData(plain_data);

	// print cipher data
	cipherText(key_data, plain_data, cipher_data, key_len, plain_len);
	printf("\n\n\nCiphertext:\n\n");
	printData(cipher_data);
	printf("\n");

	return 0;
}