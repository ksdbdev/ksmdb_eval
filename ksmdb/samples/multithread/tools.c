#include "tools.h"


/*
 * thread functions.
 */

int create_thread(THREAD_HANDLE *thread_id_ptr, ThreadProc thread_entry, void *thread_arg)
{
#ifdef WIN32
//	*thread_id_ptr = (HANDLE)_beginthread(thread_entry,0, thread_arg);		
	*thread_id_ptr = (HANDLE)_beginthreadex(0,0,thread_entry, thread_arg,0,0);		
	if ((int) (*thread_id_ptr)!=-1) return 0;
	return -1;
#else
	return pthread_create(thread_id_ptr,NULL,thread_entry, thread_arg);
#endif
}

THREAD_HANDLE get_thread_id()
{
#ifdef WIN32
	return GetCurrentThread();
#else
	return pthread_self();
#endif
}

int join_thread(THREAD_HANDLE tid)
{
#ifdef WIN32	
	return WaitForSingleObject(tid,INFINITE);

#else
	return pthread_join(tid,NULL);
#endif

}



/*Operating system interface for creating mutex variable*/
void create_mutex(mutex_t *mtx){
#ifdef WIN32
	InitializeCriticalSection(mtx);
#else
    pthread_mutex_init(mtx,0);
#endif
}

/*Operating system interface for destroying mutex variable*/
void destroy_mutex(mutex_t *mtx){
#ifdef WIN32
    DeleteCriticalSection(mtx);
#else
    pthread_mutex_destroy(mtx);
#endif
}

/*Operating system interface for locking mutex variable*/
void lock_mutex(mutex_t *mtx){
#ifdef WIN32
	EnterCriticalSection(mtx);
#else
	pthread_mutex_lock(mtx);
#endif
}

/*Operating system interface for unlocking(signal) mutex variable*/
void unlock_mutex(mutex_t *mtx){
#ifdef WIN32
    LeaveCriticalSection(mtx);
#else
    pthread_mutex_unlock(mtx);
#endif
}

void init_event(my_event *evnt,int init_state){
#ifdef WIN32
    evnt->_handle = CreateEvent(0, 0,init_state, 0); /* create event */
#else
    pthread_cond_init(&(evnt->_handle._cond), 0);                /* init condition thread */
    evnt->_handle._signaled = init_state;                        /* set initial state     */
    pthread_mutex_init(&(evnt->_handle._mtx),0);
#endif
}
void destroy_event(my_event *evnt){
#ifdef WIN32
    CloseHandle(evnt->_handle);                     /* close event handle */
#else
    pthread_cond_destroy(&(evnt->_handle._cond));   /* destroy condition thread */
    pthread_mutex_destroy(&(evnt->_handle._mtx));
#endif
}
void signal_event(my_event *evnt){
#ifdef WIN32
    /* set event to the signal state    */
    SetEvent(evnt->_handle);
#else
    /* lock mutex   */
    pthread_mutex_lock(&(evnt->_handle._mtx));
    pthread_cond_signal(&evnt->_handle._cond);   /* Unblock just one waiter     */
    evnt->_handle._signaled = 1;
    pthread_mutex_unlock(&(evnt->_handle._mtx));
#endif
}



int event_wait(my_event *evnt,int timeout){
#ifdef WIN32
    /* wait signal  */
    return WaitForSingleObject(evnt->_handle, timeout);
#else
    const size_t os_minus_one = ~0;
    int ret = 0;  /* If we don't do anything it's because it's free already */
    /* If the event is not in the signaled state, we will have to wait. */
    pthread_mutex_lock(&(evnt->_handle._mtx));

    if (!evnt->_handle._signaled) /* if signal has not been set to 1, wait by pthread_cond_... */
	{
        if (!timeout) /* no time for waiting    */{
            pthread_mutex_unlock(&(evnt->_handle._mtx));
            return WAIT_TIMEOUT;
        }else{
            struct timespec timeout_;
            if (INFINITE != timeout){
                /* set timeout  */
                struct timeval now_;
                gettimeofday(&now_, 0);
                timeout_.tv_sec = now_.tv_sec + timeout / 1000;
                timeout_.tv_nsec = (((timeout % 1000) * 1000 + now_.tv_usec) % 1000000) * 1000;
            }

            /* wait until condition thread returns control  */

			if  (INFINITE == timeout)
                ret=pthread_cond_wait(&(evnt->_handle._cond),& (evnt->_handle._mtx)) ;
            else				
                ret=pthread_cond_timedwait(&(evnt->_handle._cond),&(evnt->_handle._mtx), &timeout_);					
				


		}
    }
	else   /*another thread has set it to 1, no need to wait on pthread_cond_....!!!*/
		evnt->_handle._signaled = 0;  /*2012-12-17 add to switch the variable from 1 to 0.*/


    /* adjust signaled member   */
    switch (ret)
    {
    case 0: /* success  */
        pthread_mutex_unlock(&(evnt->_handle._mtx));
        return WAIT_OBJECT_0;
    case ETIMEDOUT:
    default:
        pthread_mutex_unlock(&(evnt->_handle._mtx));
        return WAIT_TIMEOUT;
    }
#endif
}

#ifndef WIN32
void Sleep(unsigned int millis){
  struct timespec req , rem ;
  req.tv_sec  = millis / 1000 ;
  req.tv_nsec = (millis % 1000) *1000000 ;
  while ( nanosleep(&req, &rem) == -1 )
  {
    if ( errno != EINTR ) break ;
    req.tv_sec  = rem.tv_sec ;
    req.tv_nsec = rem.tv_nsec ;
  }
}
#endif


