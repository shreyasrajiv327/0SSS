#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>  // To use the standard integer types 

// OS_SS Lab 4: Aug 2023
// Demo of building a shared library (shared object)



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

