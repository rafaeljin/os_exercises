#include <stdio.h>
#include <monitor.h>
#include <kmalloc.h>
#include <assert.h>
#define MY_HOARE 1

// Initialize monitor.
void     
monitor_init (monitor_t * mtp, size_t num_cv) {
    int i;
    assert(num_cv>0);
    mtp->next_count = 0;
    mtp->cv = NULL;
    sem_init(&(mtp->mutex), 1); //unlocked
    sem_init(&(mtp->next), 0);
    mtp->cv =(condvar_t *) kmalloc(sizeof(condvar_t)*num_cv);
    assert(mtp->cv!=NULL);
    for(i=0; i<num_cv; i++){
        mtp->cv[i].count=0;
        sem_init(&(mtp->cv[i].sem),0);
        mtp->cv[i].owner=mtp;
    }
}

// Unlock one of threads waiting on the condition variable. 
void 
cond_signal (condvar_t *cvp) {
   //LAB7 EXERCISE1: 2012080059
   cprintf("cond_signal begin: cvp %x, cvp->count %d, cvp->owner->next_count %d\n", cvp, cvp->count, cvp->owner->next_count);  
  /*
   *      cond_signal(cv) {
   *          if(cv.count>0) {
   *             mt.next_count ++;
   *             signal(cv.sem);
   *             wait(mt.next);
   *             mt.next_count--;
   *          }
   *       }
   */
   if(cvp -> count > 0){				// if exist proc in condition's wait queue
# ifdef MY_HOARE
	   monitor_t *mtp = cvp -> owner;
	   mtp -> next_count++;
	   up(&cvp -> sem);					// wake up a proc waiting for condition
	   down(&mtp -> next);				// put itself into monitor's next list
	   mtp -> next_count--;
# else 
	up(&(cvp->sem));
# endif
   }
   cprintf("cond_signal end: cvp %x, cvp->count %d, cvp->owner->next_count %d\n", cvp, cvp->count, cvp->owner->next_count);
}

// Suspend calling thread on a condition variable waiting for condition Atomically unlocks 
// mutex and suspends calling thread on conditional variable after waking up locks mutex. Notice: mp is mutex semaphore for monitor's procedures
void
cond_wait (condvar_t *cvp) {
    //LAB7 EXERCISE1: 2012080059
    cprintf("cond_wait begin:  cvp %x, cvp->count %d, cvp->owner->next_count %d\n", cvp, cvp->count, cvp->owner->next_count);
   /*
    *         cv.count ++;
    *         if(mt.next_count>0)
    *            signal(mt.next)
    *         else
    *            signal(mt.mutex);
    *         wait(cv.sem);
    *         cv.count --;
    */
    monitor_t *mtp = cvp -> owner;
    cvp -> count++;
# ifdef MY_HOARE
    if (mtp -> next_count > 0)		// if monitor's next list has proc
    	up(&mtp -> next);			// wake it up
    else
        up(&mtp -> mutex);			// else release mutex
    down(&cvp -> sem);				// wait for condition
# else
	up(&mtp -> mutex);			// release mutex
    down(&cvp -> sem);			// wait for condition
    down(&mtp -> mutex);
# endif
    cvp -> count--;
    cprintf("cond_wait end:  cvp %x, cvp->count %d, cvp->owner->next_count %d\n", cvp, cvp->count, cvp->owner->next_count);
}
