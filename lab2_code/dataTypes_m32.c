#include <stdio.h>
#include <stdlib.h>

void dataLengths(void){

	printf("sizeof(char)      = %u\n", sizeof(char));
	printf("sizeof(short)     = %u\n", sizeof(short));
	printf("sizeof(int)       = %u\n", sizeof(int));
	printf("sizeof(long)      = %u\n", sizeof(long));
	printf("sizeof(long long) = %u\n", sizeof(long long));
	printf("sizeof(void *)    = %u\n", sizeof(void *));

} // end of dataLengths()


int main()
{
    printf("Lab2: Print the size of Data Types in bytes: 32-bit version ...\n");

    dataLengths();

    return 0;
}

