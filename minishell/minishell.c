/*Elizabeth Duncan
  Homework 11 Software Systems
*/


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int main() {

    //buffer is to hold the commands that the user will type in
    char buffer[512];
    //All command-line stuff is in the bin directory
    char* path = "/bin/";
    char program[512];
    char flag[512];
    int running = 1;
    int i;


    while(1)
    {
        //Prompt
        printf("myShell>");
        fgets(buffer, 512, stdin);
        int pid = fork();
        //error check fork (from HeadFirst)
        if (pid == -1) {
            fprintf(stderr, "Can't for process: %s\n", strerror(errno));
            return 1;
            }
         //If pid !=0 then it's the parent
         if(pid){
            //parent must just wait
            wait(NULL);
         }else{
         
        sscanf(buffer, "%s %s", program, flag);
    
        char *array_of_strings[2];
    
        array_of_strings[0] = flag;
        array_of_strings[1] = NULL;
        execvp(program, array_of_strings);
        
        }
    }
    return 0;
}
