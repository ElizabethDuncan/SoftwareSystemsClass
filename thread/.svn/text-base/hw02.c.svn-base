/* Example from Figure 2.4 of Hailperin, Operating Systems and Middleware.

Copyright 2012 Max Hailperin and Modified by Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

Modified by Elizabeth Allie Duncan for:
Homework02
Software Systems Fall 2011
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>


/* Sleeps for the given number of seconds and nanoseconds.

Thread becomes available for scheduling after the given time has
elapsed, but may not be scheduled immediately.

 */
void call_nanosleep(long seconds, long nanosecs)
{
    struct timespec requested, remaining;
    requested.tv_sec = seconds;
    requested.tv_nsec = nanosecs;
    nanosleep(&requested, &remaining);
}

/*Appropriately general function that loops through printing a message and sleeping for a given amount of time. 
This function is passed number of iterations through the for loop, the seconds of sleep time (sleepfor), the nanoseconds of sleep time (sleepfor_seconds), and an indicator that differentiates print messages. 
*/
int appropriatelyGeneral(int iterations, int sleepfor, long sleepfor_seconds,int indicator){
    int i;
    
    for(i=0; i < iterations; i++){
        if(indicator == 0){
            printf("Child message printed! \n");
         }else if(indicator == 1){
            printf("Parent message printed! \n");
         }
         call_nanosleep(sleepfor, sleepfor_seconds);
    
    }
    return 0;
}

/*This is a child thread that calls appropriatelyGeneral*/
static void *child(void *ignored)
{
    int child_indicator = 0;
    /*Child thread passes 10 iterations and a sleep time of 0.5 seconds*/
    appropriatelyGeneral(10,0,500000000L,child_indicator);
    return NULL;
}

/*The main function is what is executed*/
int main(int argc, char *argv[])
{
    /*Child thread is declared along with variables*/
    pthread_t child_thread;
    int code;
    int parent_indicator = 1;
    
    /*Child thread is created and automatically starts running*/
    code = pthread_create(&child_thread, NULL, child, NULL);
    if (code) {
	fprintf(stderr, "pthread_create failed with code %d\n", code);
    }
    /*Child thread passes 10 iterations and a sleep time of 1 seconds*/
    appropriatelyGeneral(10,1,0, parent_indicator);
    return 0;
}
