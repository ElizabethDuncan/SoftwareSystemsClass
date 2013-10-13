/*Homework 06 for Software Systems
  Elizabeth Duncan
  Fall 2012
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <regex.h>

/* Text to be iterated through.*/
char tracks[][80] = {
    "I left my heart in Harvard Med School",
    "Newark,Newark - a wonderful town",
    "Dancing with a Dork",
    "From here to maternity",
    "The girl from Iwo Jima",
};

/* This function creates a regular expression from the given input search_for.
   Then it searches through the tracks to find matches.
*/
void find_track(char search_for[])
{
    regex_t regex;
    int reti;
    char msgbuf[100];
    

    /*Create regular expression from search_for*/
    reti = regcomp(&regex, search_for, 0);
    if(reti) {
        fprintf(stderr, "Could not compile regex\n");
        exit(107);
    }
    
    /*Iterate through each line of tracks*/
    int m;
    for (m=0;m<5;m++){
        /*Check if there is a match in each line*/
        if(!(reti = regexec(&regex, tracks[m], 0, NULL, 0))){
            printf("MATCH at Track %d: '%s' \n", m, tracks[m]);     
        }else if(reti == REG_NOMATCH){
            continue; 
        }else{
            regerror(reti, &regex, msgbuf, sizeof(msgbuf));
            fprintf(stderr,"Regex match failed: %s\n", msgbuf);
            exit(107);
        }
    }
}

/* This function accepts input by and checks to see if there is a '\n'.
   If there is, find_track will not work correctly, so it replaces the 
   '\n' with a '\0'. If not, it doesn't edit anything.
*/
void interpret_input(char* search_for)
{
    if(search_for[strlen(search_for) - 1] == '\n'){
        search_for[strlen(search_for) - 1] = '\0';
    }
}

int main()
{ 
    char search_for[80];
    printf("Enter regular expression: ");
    fgets(search_for, 80, stdin);
    interpret_input(search_for);
    find_track(search_for);

    return 0;
}
    
