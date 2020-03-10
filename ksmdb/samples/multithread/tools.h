#ifndef _TOOLS_H_
#define _TOOLS_H_

/*Header files */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<math.h>
#include<malloc.h>
#ifdef WIN32
#include<windows.h>
#include<process.h>
#include<share.h>
#include<io.h>
#include<sys/locking.h>
#else
#include<pthread.h>
#include<sys/types.h>
#include<sys/time.h>
#include <sched.h>
#include<errno.h>
#endif

#ifdef __cplusplus
    extern "C" {
#endif

/*
 * thread functions.
 */

#ifdef WIN32
typedef HANDLE THREAD_HANDLE ;

typedef unsigned int (_stdcall *ThreadProc)(void *);

#else
typedef pthread_t THREAD_HANDLE ;
typedef void* (*ThreadProc)(void *);
#endif

/*
 *  return 0: success.
 *		   -1: failure.
 */
int create_thread(THREAD_HANDLE *thread_id_ptr, ThreadProc thread_entry, void *thread_arg);

THREAD_HANDLE get_thread_id();

int join_thread(THREAD_HANDLE tid);



#ifdef WIN32
typedef CRITICAL_SECTION mutex_t;
#define PTHREAD_CANCELLED 0
#define THREAD_RETURN_VALUE PTHREAD_CANCELLED
#define THREAD_RETURN_TYPE                                              unsigned __stdcall

#else
#define WAIT_TIMEOUT  0x00000102L
#define WAIT_OBJECT_0     0
#define INFINITE      -1
typedef pthread_mutex_t mutex_t;
typedef unsigned int DWORD;
#ifndef PTHREAD_CANCELED
#define PTHREAD_CANCELED                                                0
#endif
#define THREAD_RETURN_TYPE                                              void *
#define THREAD_RETURN_VALUE                                             PTHREAD_CANCELED

#endif

#ifndef WIN32
typedef struct {
    pthread_mutex_t     _mtx;
    pthread_cond_t      _cond;
    int                 _signaled;
} HANDLE;
#endif

typedef struct{
    HANDLE _handle;
}my_event;

/*Initialize the event object */
void init_event(my_event *evnt,int init_state);
/*Wait on the event object for specified time */
int  event_wait(my_event *evnt,int timeout);



/*Signal the event */
void signal_event(my_event *evnt);
/*destroy the event */
void destroy_event(my_event *evnt);


void create_mutex(mutex_t *mtx);
void destroy_mutex(mutex_t *mtx);
void lock_mutex(mutex_t *mtx);
void unlock_mutex(mutex_t *mtx);
#ifndef WIN32
void Sleep(unsigned int millis);
#endif



#ifdef __cplusplus
	}
#endif


#endif
