#ifndef PTHREAD_H
#define PTHREAD_H

#ifdef __cplusplus  
extern "C" {  
#endif 

#include <time.h>

// Copied from: https://www.qnx.com/developers/docs/6.4.1/neutrino/lib_ref/s/sched_param.html

struct sched_param {
    int32_t  sched_priority;
    int32_t  sched_curpriority;
    union {
        int32_t  reserved[8];
        struct {
            int32_t  __ss_low_priority;
            int32_t  __ss_max_repl;
            struct timespec     __ss_repl_period;
            struct timespec     __ss_init_budget;
        }           __ss;
    }           __ss_un;
};

#define sched_ss_low_priority   __ss_un.__ss.__ss_low_priority
#define sched_ss_max_repl       __ss_un.__ss.__ss_max_repl
#define sched_ss_repl_period    __ss_un.__ss.__ss_repl_period
#define sched_ss_init_budget    __ss_un.__ss.__ss_init_budget

// Copied from: https://refspecs.linuxbase.org/LSB_3.0.0/LSB-PDA/LSB-PDA/libpthread-ddefs.html

#define PTHREAD_SCOPE_SYSTEM	0
#define PTHREAD_MUTEX_DEFAULT	1
#define PTHREAD_MUTEX_NORMAL	1
#define PTHREAD_SCOPE_PROCESS	1
#define PTHREAD_MUTEX_RECURSIVE	2
#define PTHREAD_RWLOCK_DEFAULT_NP	2
#define PTHREAD_MUTEX_ERRORCHECK	3
//#define pthread_cleanup_pop(execute)	_pthread_cleanup_pop(& _buffer,(execute));}
#define __LOCK_INITIALIZER	{ 0, 0 }
#define PTHREAD_RWLOCK_INITIALIZER	{ __LOCK_INITIALIZER, 0, NULL, NULL, NULL,PTHREAD_RWLOCK_DEFAULT_NP, PTHREAD_PROCESS_PRIVATE }
#define PTHREAD_MUTEX_INITIALIZER	{0,0,0,PTHREAD_MUTEX_NORMAL,__LOCK_INITIALIZER}
#define pthread_cleanup_push(routine,arg)	{struct _pthread_cleanup_buffer _buffer;_pthread_cleanup_push(& _buffer,(routine),(arg));
#define PTHREAD_COND_INITIALIZER	{__LOCK_INITIALIZER,0}

struct _pthread_cleanup_buffer
{
  void (*__routine) (void *);
  void *__arg;
  int __canceltype;
  struct _pthread_cleanup_buffer *__prev;
}
 ;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
typedef long long int __pthread_cond_align_t;

typedef unsigned long int pthread_t;
struct _pthread_fastlock
{
  long int __status;
  int __spinlock;
}
 ;

typedef struct _pthread_descr_struct *_pthread_descr;

typedef struct
{
  int __m_reserved;
  int __m_count;
  _pthread_descr __m_owner;
  int __m_kind;
  struct _pthread_fastlock __m_lock;
}
pthread_mutex_t;
typedef struct
{
  int __mutexkind;
}
pthread_mutexattr_t;

typedef struct
{
  int __detachstate;
  int __schedpolicy;
  struct sched_param __schedparam;
  int __inheritsched;
  int __scope;
  size_t __guardsize;
  int __stackaddr_set;
  void *__stackaddr;
  unsigned long int __stacksize;
}
pthread_attr_t;

typedef struct
{
  struct _pthread_fastlock __c_lock;
  _pthread_descr __c_waiting;
  char __padding[48 - sizeof (struct _pthread_fastlock) -
		 sizeof (_pthread_descr) - sizeof (__pthread_cond_align_t)];
  __pthread_cond_align_t __align;
}
pthread_cond_t;
typedef struct
{
  int __dummy;
}
pthread_condattr_t;

typedef struct _pthread_rwlock_t
{
  struct _pthread_fastlock __rw_lock;
  int __rw_readers;
  _pthread_descr __rw_writer;
  _pthread_descr __rw_read_waiting;
  _pthread_descr __rw_write_waiting;
  int __rw_kind;
  int __rw_pshared;
}
pthread_rwlock_t;
typedef struct
{
  int __lockkind;
  int __pshared;
}
pthread_rwlockattr_t;

#define PTHREAD_CREATE_JOINABLE	0
#define PTHREAD_INHERIT_SCHED	0
#define PTHREAD_ONCE_INIT	0
#define PTHREAD_PROCESS_PRIVATE	0
#define PTHREAD_CREATE_DETACHED	1
#define PTHREAD_EXPLICIT_SCHED	1
#define PTHREAD_PROCESS_SHARED	1

#define PTHREAD_CANCELED	((void*)-1)
#define PTHREAD_CANCEL_DEFERRED	0
#define PTHREAD_CANCEL_ENABLE	0
#define PTHREAD_CANCEL_ASYNCHRONOUS	1
#define PTHREAD_CANCEL_DISABLE	1

// Copied from: https://pubs.opengroup.org/onlinepubs/7908799/xsh/pthread.h.html

int   pthread_attr_destroy(pthread_attr_t *);
int   pthread_attr_getdetachstate(const pthread_attr_t *, int *);
int   pthread_attr_getguardsize(const pthread_attr_t *, size_t *);
int   pthread_attr_getinheritsched(const pthread_attr_t *, int *);
int   pthread_attr_getschedparam(const pthread_attr_t *,
          struct sched_param *);
int   pthread_attr_getschedpolicy(const pthread_attr_t *, int *);
int   pthread_attr_getscope(const pthread_attr_t *, int *);
int   pthread_attr_getstackaddr(const pthread_attr_t *, void **);
int   pthread_attr_getstacksize(const pthread_attr_t *, size_t *);
int   pthread_attr_init(pthread_attr_t *);
int   pthread_attr_setdetachstate(pthread_attr_t *, int);
int   pthread_attr_setguardsize(pthread_attr_t *, size_t);
int   pthread_attr_setinheritsched(pthread_attr_t *, int);
int   pthread_attr_setschedparam(pthread_attr_t *,
          const struct sched_param *);
int   pthread_attr_setschedpolicy(pthread_attr_t *, int);
int   pthread_attr_setscope(pthread_attr_t *, int);
int   pthread_attr_setstackaddr(pthread_attr_t *, void *);
int   pthread_attr_setstacksize(pthread_attr_t *, size_t);
int   pthread_cancel(pthread_t);
//void  pthread_cleanup_push(void*), void *);
void  pthread_cleanup_pop(int);
int   pthread_cond_broadcast(pthread_cond_t *);
int   pthread_cond_destroy(pthread_cond_t *);
int   pthread_cond_init(pthread_cond_t *, const pthread_condattr_t *);
int   pthread_cond_signal(pthread_cond_t *);
int   pthread_cond_timedwait(pthread_cond_t *, 
          pthread_mutex_t *, const struct timespec *);
int   pthread_cond_wait(pthread_cond_t *, pthread_mutex_t *);
int   pthread_condattr_destroy(pthread_condattr_t *);
int   pthread_condattr_getpshared(const pthread_condattr_t *, int *);
int   pthread_condattr_init(pthread_condattr_t *);
int   pthread_condattr_setpshared(pthread_condattr_t *, int);
int   pthread_create(pthread_t *, const pthread_attr_t *,
          void *(*)(void *), void *);
int   pthread_detach(pthread_t);
int   pthread_equal(pthread_t, pthread_t);
void  pthread_exit(void *);
int   pthread_getconcurrency(void);
int   pthread_getschedparam(pthread_t, int *, struct sched_param *);
void *pthread_getspecific(pthread_key_t);
int   pthread_join(pthread_t, void **);
int   pthread_key_create(pthread_key_t *, void (*)(void *));
int   pthread_key_delete(pthread_key_t);
int   pthread_mutex_destroy(pthread_mutex_t *);
int   pthread_mutex_getprioceiling(const pthread_mutex_t *, int *);
int   pthread_mutex_init(pthread_mutex_t *, const pthread_mutexattr_t *);
int   pthread_mutex_lock(pthread_mutex_t *);
int   pthread_mutex_setprioceiling(pthread_mutex_t *, int, int *);
int   pthread_mutex_trylock(pthread_mutex_t *);
int   pthread_mutex_unlock(pthread_mutex_t *);
int   pthread_mutexattr_destroy(pthread_mutexattr_t *);
int   pthread_mutexattr_getprioceiling(const pthread_mutexattr_t *,
          int *);
int   pthread_mutexattr_getprotocol(const pthread_mutexattr_t *, int *);
int   pthread_mutexattr_getpshared(const pthread_mutexattr_t *, int *);
int   pthread_mutexattr_gettype(const pthread_mutexattr_t *, int *);
int   pthread_mutexattr_init(pthread_mutexattr_t *);
int   pthread_mutexattr_setprioceiling(pthread_mutexattr_t *, int);
int   pthread_mutexattr_setprotocol(pthread_mutexattr_t *, int);
int   pthread_mutexattr_setpshared(pthread_mutexattr_t *, int);
int   pthread_mutexattr_settype(pthread_mutexattr_t *, int);
int   pthread_once(pthread_once_t *, void (*)(void));
int   pthread_rwlock_destroy(pthread_rwlock_t *);
int   pthread_rwlock_init(pthread_rwlock_t *,
          const pthread_rwlockattr_t *);
int   pthread_rwlock_rdlock(pthread_rwlock_t *);
int   pthread_rwlock_tryrdlock(pthread_rwlock_t *);
int   pthread_rwlock_trywrlock(pthread_rwlock_t *);
int   pthread_rwlock_unlock(pthread_rwlock_t *);
int   pthread_rwlock_wrlock(pthread_rwlock_t *);
int   pthread_rwlockattr_destroy(pthread_rwlockattr_t *);
int   pthread_rwlockattr_getpshared(const pthread_rwlockattr_t *,
          int *);
int   pthread_rwlockattr_init(pthread_rwlockattr_t *);
int   pthread_rwlockattr_setpshared(pthread_rwlockattr_t *, int);
pthread_t
      pthread_self(void);
int   pthread_setcancelstate(int, int *);
int   pthread_setcanceltype(int, int *);
int   pthread_setconcurrency(int);
int   pthread_setschedparam(pthread_t, int ,
          const struct sched_param *);
int   pthread_setspecific(pthread_key_t, const void *);
void  pthread_testcancel(void);

#ifdef __cplusplus  
}  
#endif  

#endif
