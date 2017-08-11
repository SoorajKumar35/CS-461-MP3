make: md5break.c
	gcc md5break.c -o md5break -lcrypto -lssl -Wall -g -gdwarf-3