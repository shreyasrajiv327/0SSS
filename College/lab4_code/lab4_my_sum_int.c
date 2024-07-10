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

static int my_sum_int_sint = 1000;

int64_t my_sum_int(int32_t num_args, ...) {  /* Variable no. of params */ 

    int64_t total = 0;
    va_list ap;
    int32_t i;

    printf("my_sum_int: static var address: %p\n", &my_sum_int_sint);
    printf("my_sum_int: my_sum_int() code address: %p\n",
            my_sum_int);


    va_start(ap, num_args);

    for ( i = 0; i < num_args; i++) {
      total += va_arg(ap, int32_t);
    }

    va_end(ap);

    return total;
}

