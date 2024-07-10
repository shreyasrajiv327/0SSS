#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>  // To use the standard integer types 

// OS_SS Lab 4: Aug 2023
// Demo of building a static library 

// Commands to build a static library
// Note: The path mentioned here should match with your own directory structure

// gcc -c -fpic -o libmy_sum_int.a lab4_my_sum_int.c
// gcc -L/home/smouli/RVU/OS/Lab4/lib/a -o my_sum_int lab4_my_sum_int_main.c  -lmy_sum_int
// Note: Make sure that the library file with -l option is given at the end
// remember also that the lib file should start with lib and end with .a
// But while giving it in the command line for the 2nd command, 
// do not include lib in the front and .a at the end, drop them.


// prototype of the function defined in a static libary to be linked
extern int64_t my_sum_int(int32_t num_args, ...);

static int my_sum_int_main_sint = 2000;

int32_t main(){

    printf("OS_SS-Lab 4: Demo of developing static library.\n");
	// Get the logical addresses of code and data of this program
    printf("my_sum_int_main: static var address: %p\n",
            &my_sum_int_main_sint);
    printf("my_sum_int_main: main() code address: %p\n",
            main);            
           

	int32_t num_params = 2;
	int32_t i = 20;
	int32_t j = 35;
	
    printf(  "Sum  = %lld\n", (long long) my_sum_int(num_params,  i, j)  );

    return 0;
    
 } // end of main()

