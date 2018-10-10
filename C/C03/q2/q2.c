#include <stdio.h>
#include <stdlib.h>
#include "Q2Test.h"

int main(int argc, char** argv) {
	
	if ( argc != 3 ) {
		printf("Invocation:  q1 <integer1> <integer2>\n");
		return 1;
	}
	
	int integer1 = atoi(argv[1]);
	int integer2 = atoi(argv[2]);
	
	if ( !Q2Test(integer1, integer2) ) {
		printf("Failed a requirement.\n");
		return 2;
	}
	
	printf("Met all requirements.\n");

   return 0;
}
