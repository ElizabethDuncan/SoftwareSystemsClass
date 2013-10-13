#include <stdio.h>
#include <unistd.h>
#include <string.h>

/* tee.c allows the user to pipe standard inputs from a source to as many as 
 * ten files and the command line
 */
int main (int argc, char **argv) {

    /* Declare variables */
    char help_text[] = "Tee takes input from the command line and prints that input to the command line as well as saving the imput to a file. With a '-a', tee will append to the file (rather than overwrite, which is the default). tee can also output to multiple files up to a maximum of ten.\n";
    char version_text[] = "This is version 0.1.  Come at me, bro.\nWritten by Elizabeth 'Alliecat' Duncan and Kyle 'The Rocket' McConnaughay.\n";
    
    int fopen_option = 0; /* The default fopen mode is "w" */
    char ch; /* ch is used to test the optional arguments */
    FILE *file_array[10]; /* file_array stores the names of any outputs for 
                           * writing to them using fprintf
                           */
    FILE *repeat;
    char line[80]; /* line is used to write successive lines to the files 
                    * specified in file_array
                    */
    
    int i; /* i is used in for loops */    
    
    /* check for optional arguments */
    while ((ch = getopt(argc, argv, "ahv")) != EOF) { 
     
        switch (ch) {
            /* This sets the fopen mode to "a" */
            case 'a':
                fopen_option = 1; 
                break;
                
            /* print help_text */
            case 'h':
                printf("%s\n", help_text); 
                return 0;
                
             /* print version_text */
             case 'v':
                printf("%s\n", version_text); 
                return 0;
                
             /* otherwise, an unrecognized optarg was passed */
             default:
                fprintf(stderr, "Unkown option: '%s'\n", optarg); 
                return 1;
        }
    }
    
    /* adjust argc and argv to account for the optional parameters we just 
     * iterated through
     */
    argc -= optind;
    argv += optind;
    
    /* fill file_array with the intended destinations of standard output */
    for (i = 0; i < argc; i++) {
        
        /* check to see if writing ("w") or appending ("a") to the files 
         * and create file_array
         */       
        if (fopen_option == 0) {
            file_array[i] = fopen(argv[i], "w");
        } else if (fopen_option == 1) {
            file_array[i] = fopen(argv[i], "a");
        }
    }
    
    /* for each line from standard input, write to each destination in 
     * file_array
     */
    while (fscanf(stdin, "%79[^\n]\n", line) == 1) {
        for (i = 0; i < argc; i++) {
            fprintf(file_array[i], "%s\n", line);
        }
        /*Don't print out the newly made - file */
        if(strcmp(line, "-")){
            printf("%s\n", line);
            }
    }
    
    /* close all the files */
    for (i = 0; i < argc; i++) {
        fclose(file_array[i]);
    }
    
    if(!strcmp(argv[0], "-")){
        repeat = fopen("-", "r");
        while (fscanf(repeat, "%79[^\n]\n", line) == 1) {
            if(strcmp(line, "-")){
            printf("%s\n", line);
            }
        }
        fclose(repeat);
        if (remove("-") == -1){
            perror("Error in deleting a file\n");
        }
    }
    
    /* great success! */
    return 0;

}
