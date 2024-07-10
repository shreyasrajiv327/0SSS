1. Build both 32-bit and 64-bit versions
1a. 32-bit application
gcc   -o   my_sum_int_m32   lab4_my_sum_int.c   lab4_my_sum_main.c   -m32
1b. 64-bit application
gcc -o my_sum_int_m64  lab4_my_sum_int.c  lab4_my_sum_main.c 

2. Under the lib/a directory demo of creating a static library (under lib/a directory)
2a. Build a static library with –c and -fPIC options:
 gcc  -c   -fPIC    -o   libmy_sum_int.a   lab4_my_sum_int.c
 
 2b. Build an executable by linking it with the static library by giving its path
 // Note that the same convention of -l option at the end and the file name
 // is starting with lib and ending with .a is not to be included in the -l option
//  Static library is included along with the executable
 // CAUTION: -l option should be at the end always and without lib and .a 
 gcc    -L/home/smouli/RVU/OS/Lab4/lib/a    -o  my_sum_int
            lab4_my_sum_int_main.c     -lmy_sum_int

3. Now build shared object (shared library) (under lib/so directory
3a. Build shared object of lab4_my_sum_int.c in 64-bit mode
// Position Independent Code: -fPIC option
// -c is important because this file does not have main
// -o should have the lib at the beginning and .so at the end, without lib and .so
gcc   -c   -fPIC   lab4_my_sum_int.c     // it only compiles and generates .o file
gcc    -shared   -o libmy_sum_int.so  lab4_my_sum_int.o 

3b. Set LD_LIBRARY_PATH variable used by the loader
export LD_LIBRARY_PATH="/home/smouli/RVU/OS/lab4/lib/so"
echo $LD_LIBRARY_PATH

Note: The above step is required because the loader looks for the shared object to be used by the executable while running it, from the directory pointed to by the
LD_LIBRARY_PATH environment variable.

3c. Build an application using the shared object file and the main file
// Note that the same convention of -l option at the end and the file name
// is starting with lib and ending with .so is not to be included in the -l option
// LD_LIBRARY_PATH is to be set here because the so is loaded during run time.
// CAUTION: -l option should be at the end always
gcc -o my_sum_int -L/home/smouli/RVU/OS/Lab4/lib/so  lab4_my_sum_int_main.c -lmy_sum_int
 
Using the command mentioned in the step 4 below:
You can compare the file size of the executable built with dynamic lib (.so)
 and static lib (.a) and notice that the one with static lib will be larger than the
 one built with the dynamic lib. 
4. Compare the sizes of the executables.
     The size of the executables can be compared by running the size command with executable
     name as the parameter to it. Run the below command from the both the respective directories 
     of static and dynamic libraries.
size my_sum_int  

5. Find out the list of .so (shared objects) used by an executable:
  objdump   -p   my_sum_int | grep NEEDED
  ps –all    /* Find the PID of the my_sum_int executable running forever */
  lsof –p pid_of_my_sum_int    | grep my_sum_int
  lsof –u smouli | grep my_sum_int    /* instead of smouli give your username */
  kill -9 pid_of_my_sum_int
gcc /Users/shreyasr/Documents/OSSS/lab4_code/lib/a  