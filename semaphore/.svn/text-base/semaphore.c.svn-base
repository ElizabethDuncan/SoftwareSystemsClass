#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <errno.h>
#include <string.h>

//Structures defined
typedef struct {
	pthread_mutex_t mutex;
} MutexWrapper;

typedef struct {
	pthread_cond_t cond;
} CondWrapper;

typedef struct { 
  int value, wakeups;
  MutexWrapper *mutex;
  CondWrapper *cond;
} Semaphore;

// Mutex wrapper commented out because more specific definition given by a structure
//typedef pthread_mutex_t MutexWrapper;

//Function definitions
CondWrapper *make_cond ();
void cond_wait (CondWrapper *cond, MutexWrapper *mutex);
void cond_signal (CondWrapper *cond);
Semaphore *make_semaphore (int value);
void sem_signal (Semaphore *semaphore);
void sem_wait (Semaphore *semaphore);
void perror_exit (char *s);
void *check_malloc(int size);
MutexWrapper *make_mutex ();
void mutex_lock (MutexWrapper *mutex);
void mutex_unlock (MutexWrapper *mutex);

//Variables
int i;

//Condition functions
CondWrapper *make_cond () {
	CondWrapper *my_cond = (CondWrapper *)malloc(sizeof(CondWrapper));
		int status; 
	    if (my_cond == NULL) {
	    	error("malloc failed in make_cond");
	    }
		status = pthread_cond_init(&(my_cond->cond), NULL);
	    if (!status) {
			error("pthread_cond_init failed in make_cond");
	    }
		return my_cond;
}
void cond_wait (CondWrapper *my_cond, MutexWrapper *my_mutex) {
	int status;
	status = pthread_cond_wait (&(my_cond->cond), &(my_mutex->mutex));
	if (!status) {
		error("cond_wait failed");
	}
}

void cond_signal (CondWrapper *my_cond) {
	int status;
	status = pthread_cond_signal(&(my_cond->cond));
	if (!status) {
		error("cond_signal failed");
	}
}

//Semaphore functions
Semaphore *make_semaphore (int value) {
  Semaphore *semaphore = check_malloc (sizeof(Semaphore));
  semaphore->value = value;
  semaphore->wakeups = 0;
  semaphore->mutex = make_mutex ();
  semaphore->cond = make_cond ();
  return semaphore;
}

void sem_signal (Semaphore *semaphore) {
  mutex_lock (semaphore->mutex);
  semaphore->value++;

  if (semaphore->value <= 0) {
    semaphore->wakeups++;
    cond_signal (semaphore->cond);
  }
  mutex_unlock (semaphore->mutex);
}

void sem_wait (Semaphore *semaphore) {
	mutex_lock (semaphore->mutex);
  	semaphore->value--;
  	if (semaphore->value > 1) {
		for(i = 0; i < semaphore->wakeups; i++){
			cond_wait(semaphore->cond, semaphore->mutex);
		}
	semaphore->wakeups = 0;
	}
  	mutex_unlock (semaphore->mutex);
}

//Utility code (given by Allen Downey)
void perror_exit (char *s)
{
  perror (s);
  exit (-1);
}

void *check_malloc(int size)
{
  void *p = malloc (size);
  if (p == NULL) perror_exit ("malloc failed");
  return p;
}

MutexWrapper *make_mutex ()
{
  MutexWrapper *my_mutex = check_malloc (sizeof(MutexWrapper));
  int n = pthread_mutex_init (&(my_mutex->mutex), NULL);
  if (n != 0) perror_exit ("make_lock failed"); 
  return my_mutex;
}

void mutex_lock (MutexWrapper *my_mutex)
{
  int n = pthread_mutex_lock (&(my_mutex->mutex));
  if (n != 0) perror_exit ("lock failed");
}

void mutex_unlock (MutexWrapper *my_mutex)
{
  int n = pthread_mutex_unlock (&(my_mutex->mutex));
  if (n != 0) perror_exit ("unlock failed");
}