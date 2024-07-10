#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>  // To use the standard integer types 

// OS_SS Lab 4: Aug 2023
// Demo of building a shared library (shared object)


// Building an executable using the shared object created by giving a reference to it
// gcc -o my_sum_int -L/home/smouli/RVU/OS/Lab4/lib/so lab4_my_sum_int_main.c -lmy_sum_int
// The shared object is not included along with the executable.
// It is opened and used while the program is running and it can be shared by 
// mulitple applications simultaneously.
// Set the LD_LIBRARY_PATH environment variable using the below command
// export LD_LIBRARY_PATH="/home/smouli/RVU/OS/Lab4/lib/so"
// Check the value is set properly by using the below command (remember to include $)
// echo $LD_LIBRARY_PATH
// Run the application using the command below:
// ./my_sum_int
// It will run forever, without stopping it through another Terminal do the following
// Get the PID of this process using the command
// ps -all
// Output: 0 R  1000    1503     323 99  80   0 -   698 -      pts/0    00:00:08 my_sum_int
// Note down the PID of the my_sum_int, here it is 1503
// Based on the PID, you get run the below commands. Remember to replace 1503 value
// lsof -p 1503
// The above command lists all the resources this process uses, to get only my_sum_int
// lsof -p 1503 | grep my_sum_int
// Output would show that this process not only uses the executable file, and also .so file
// Kill the above process with the below command
// kill -9 1503
// You can see that your program terminats with a message 




// prototype of the function defined in a shared object
extern int64_t my_sum_int(int32_t num_args, ...);

static int my_sum_int_main_sint = 2000;

int32_t main(){

    printf("OS_SS-Lab 4: Demo of developing shared object library.\n");

	// Get the logical addresses of code and data of this program
    printf("my_sum_int_main: static var address: %p\n",
            &my_sum_int_main_sint);
    printf("my_sum_int_main: main() code address: %p\n",
            main);            
            

	int32_t num_params = 2;
	int32_t i = 20;
	int32_t j = 35;
	
    printf(  "Sum  = %lld\n", (long long) my_sum_int(num_params,  i, j)  );


    // ps -all to get the PID of this program and try the below cmd
    // Make this program run forever to try out the below command
    // lsof -p pid | grep my_sum_int
    // To get the list of open files by this program or process
    // lsof -u smouli gives the list of files opened by an user  
    // lsof -u smouli | grep my_sum_int    // this command only lists files with my_sum_int  
    // To make this program to run forever added the following lines
    // kill the program with kill -9 pid
    
    printf("I am going to run forever!!!\n");
	while(1); 

    
    return 0;
    
 } // end of main()

