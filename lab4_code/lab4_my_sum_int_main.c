#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>  // To use the standard integer types 

// OS_SS Lab 4: Aug 2023

// commands to build a 32-bit application and run:
// gcc -o my_sum_int_m32 lab4_my_sum_int.c lab4_my_sum_int_main.c -m32
// ./my_sum_int_m32

// commands to build a 64-bit application and run:
// gcc -o my_sum_int_m64 lab4_my_sum_int.c lab4_my_sum_int_main.c
// ./my_sum_int_m64

// Note: For 64-bit application, no need to mention -m64
// gcc default builds a 64-bit application
// Observe the pointer addresses and their widths, printed in Hex format
// In 32-bit mode, it will be 32-bit wide, in 64-bit mode, it will 48-bit wide
// The reason is the 64-bit processor the program runs on uses only 48-bit 
// address lines.



// Demo of writing a portable code across different platforms 

extern int64_t my_sum_int(int32_t num_args, ...);

static int my_sum_int_main_sint = 2000;

int32_t main(){

    printf("OS-Lab 4: Demo of differences in addresses of 32-bit and 64-bit apps\n");
	// Get the logical addresses of code and data of this program
    printf("my_sum_int_main: static var address: %p\n",
            &my_sum_int_main_sint);
    printf("my_sum_int_main: main() code address: %p\n",
            main);            
           

	int32_t num_params = 2;
	int32_t i = 23;
	int32_t j = 35;
	
    printf(  "Sum  = %lld\n", (long long) my_sum_int(num_params,  i, j)  );

    //printf("I am going to run forever!!!\n");
	//while(1);

    
    return 0;
    
 } // end of main()

