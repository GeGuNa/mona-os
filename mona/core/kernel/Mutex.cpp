/*!
    \file  Mutex.cpp
    \brief class kMutex

    Copyright (c) 2002, 2003, 2004 Higepon and the individuals listed on the ChangeLog entries.
    All rights reserved.
    License=MIT/X License

    \author  HigePon
    \version $Revision$
    \date   create:2004/01/12 update:$Date$
*/

#include <sys/HList.h>
#include "Mutex.h"
#include "io.h"
#include "syscalls.h"

/*----------------------------------------------------------------------
    KMutex  *** don't allocate this object at stack! ***
----------------------------------------------------------------------*/
KMutex::KMutex() : refcount_(1), owner_(NULL)
{
    waitList_ = new HList<Thread*>();
}

KMutex::~KMutex()
{
    if (waitList_->size() != 0) {
        g_console->printf("KMutex has waiting threads!!\n");
    }
    delete waitList_;
}

int KMutex::lock(Thread* thread, int timeoutTick /* = 0 */)
{
    enter_kernel_lock_mode();
    /* lock OK */
    if (!isLocked()) {
        owner_ = thread;
    /* lock NG, so wait */
    } else {
        waitList_->add(thread);
        if (0 == timeoutTick) {
            g_scheduler->WaitEvent(thread, MEvent::MUTEX_UNLOCKED);
        } else {
            g_scheduler->Sleep(thread, timeoutTick);
            // todo
            g_scheduler->WaitEvent2(thread, MEvent::SLEEP, MEvent::MUTEX_UNLOCKED);
        }
        g_scheduler->SwitchToNext();

        /* not reached */
    }
    exit_kernel_lock_mode();

    // Returns the reason for return
    return MEvent::MUTEX_UNLOCKED;
}

int KMutex::tryLock(Thread* thread)
{
    int result;
    enter_kernel_lock_mode();

    /* lock OK */
    if (!isLocked()) {
        owner_ = thread;
        result = MONA_SUCCESS;
    } else {
        result = MONA_FAILURE;
    }

    exit_kernel_lock_mode();
    return result;
}

int KMutex::unlock()
{
    /* not locked */
    if (!isLocked()) {
        return MONA_SUCCESS;
    }

    enter_kernel_lock_mode();

    if (waitList_ ->size() == 0) {
        owner_ = NULL;
    }
    else {
        owner_ = waitList_->removeAt(0);
        g_scheduler->EventComes(owner_, MEvent::MUTEX_UNLOCKED);
        g_scheduler->SwitchToNext();

        /* not reached */
    }

    exit_kernel_lock_mode();
    return MONA_SUCCESS;
}

int KMutex::checkSecurity(Thread* thread)
{
    return 0;
}

void KMutex::addRef()
{
    refcount_++;
}

void KMutex::releaseRef()
{
    refcount_--;
    if (refcount_ == 0)
    {
        delete this;
    }
}
