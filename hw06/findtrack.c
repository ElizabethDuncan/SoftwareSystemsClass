/*Homework 06 for Software Systems
  Elizabeth Duncan
  Fall 2012
*/


#include <stdio.h>
#include <string.h>


char tracks[][80] = {
    "I left my heart in Harvard Med School",
    "Newark,Newark - a wonderful town",
    "Dancing with a Dork",
    "From here to maternity",
    "The girl from Iwo Jima",
};

/*
char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};
*/
void find_track(char search_for[])
{
    int i;
    for (i=0;i<5;i++) {
        if(strstr(tracks[i], search_for))
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
 
 void interpret_input(char *search_for) {
 /*Need to use malloc?*/
    if(search_for[strlen(search_for) - 1] == '\n'){
        search_for[strlen(search_for) - 1] = '\0';
    }
}

int main()
{
    char search_for[80];
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    interpret_input(&search_for);
   /* search_for[strlen(search_for) - 1] = '\0';*/
    find_track(search_for);
    return 0;
}
    
