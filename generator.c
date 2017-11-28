/*
 * usage: ./Generator "<Message>" <offset>
 * This program will take a given message and starting from <offset> iterate through possible rand seeds till it comes across one where each character can be XORed against a sequential rand value generated in the order equal to it's index.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[]){
	//Create and init variables
	int count = -1, failed = 0, i=0;
	unsigned int offset = 0;
	char message[512];
	memset(message,0,511);

	//read arguments
	if(argc==3){
		strcpy(message,argv[1]);
		offset=atol(argv[2]);
	}

	//prompt message and offset if not given as arguments
	if(argc==1){
	fflush(stdin);
	printf("Enter message: ");
	scanf("%[^\n]%*c", &message);

	fflush(stdin);
	printf("Enter offset: ");
	scanf("%u", &offset);
	}

	//Begin calculation
	do {
		failed=0;
		count++;

		//Fail if upper bound of unsigned int hit.
		if((offset+count)>4294967295){
			printf("FAILED! Upper bound reached.\n");
			return 0;
		}

		//Show progress
		printf("Iteration number: %d -- Checking seed: %u\r",count, offset+count);
		//Seed rand and check each character is still a printable symbol, failing if not.
		srand(offset+count);
		for(i=0;i<strlen(message); i++){
			char result = message[i] ^ rand();
			if((result < 32) || (result>126)){
				failed=1;
				break;
			}
		}
	} while(failed);

	//Print the found seed and encoded string.
	printf("Success!\nIterations:%d\nSeed:%u\nEncoded:'",count,count+offset);
	srand(count+offset);
	for(i=0;i<strlen(message); i++)
		putc(message[i] ^ rand(), stdout);
	printf("'\n");
	return 0;
}
