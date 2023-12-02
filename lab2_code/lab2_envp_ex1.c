#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

char * env_var;
void print_env_val(char * env_var, char * envp[]);

int main(int argc, char * argv[], char * envp[])
{
  
   env_var = "USER";
   printf("\nLab2: Printing the content of the env var %s", env_var);
   print_env_val(env_var,envp);

   env_var = "OLDPWD";
   printf("\nLab2: Printing the content of the env var %s", env_var);
   print_env_val(env_var, envp);
  
    return 0;
}
void print_env_val(char * env_var, char * envp[]){
    int i=0;
   while(envp[i]!=NULL)
   {  
       if(strncmp(envp[i],env_var,4)==0 && (envp[i][strlen(env_var)] == '='))
       {
        printf("\n%s",envp[i]);
       }
       i++;
   }
} 
