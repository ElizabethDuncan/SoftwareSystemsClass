/* Elizabeth Duncan
   Homework 13
   Software Systems
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h> 

// this function will be called recursively to grep every argument
void forkeverything(int argc, char* argv[]){
	
    int fd[2];
    int pidstatus;
    char input_buffer[1000];
    
	//Create pipe and error check
    if(pipe(fd) == -1){
        fprintf(stderr, "Can't create the pipe");
    }
    
	//Fork!
    int pid = fork();

    //error check the fork
    if (pid == -1) {
        fprintf(stderr, "Can't for process: %s\n", strerror(errno));
        exit(1);
        }

    //If pid=0 then it's the child of the fork
    if(!pid){  
	    //If there is no input, print the buffer
        if(argc == 0) {
            while(fgets(input_buffer, 1000,stdin)){;
                printf("%s", input_buffer);
            }
        }
        // If there is input, grep the input together
        if(argc > 0){
			//Format grep command from given arguments
        	char *array_of_strings[3];
        	array_of_strings[0] = "grep";
        	array_of_strings[1] = argv[0];
        	array_of_strings[2] = NULL;
			//Close the pipes
        	close(fd[0]);
        	dup2(fd[1],1);
			//Call grep using the formated command above
        	execvp("grep", array_of_strings); 
        }       
    
    //Else the pid it is the parent 
    //Parent must wait for the child to finish (so it doesn't kill the child)
    }else{
    
        if(argc > 0){
            if(waitpid(pid, &pidstatus, 0) == -1){
                printf("Waiting for child\n");
                exit(1);
            }
        
		//Close the pipes
        dup2(fd[0],0);
        close(fd[1]);

		//Recursively call this function to eventuall fork everything!
        forkeverything(argc-1,argv+1);
        }  
    }
}

// Accept given parameters and fork each pair of input
int main(int argc, char *argv[]){
    forkeverything(argc-1, argv+1);
    return 0;
}
