// Thread-Local Storage Implementation from:
// http://alex.tapmania.org/2011/03/simple-thread-local-storage-with-pthreads.html

#pragma once

#include <pthread.h>

template<typename T>
class thread_local_storage
{
private:
    pthread_key_t key_;

public:
    thread_local_storage()
    {
        pthread_key_create(&key_, NULL);
    }

    ~thread_local_storage()
    {
        pthread_key_delete(key_);
    }

    thread_local_storage& operator =(T* p)
    {
        pthread_setspecific(key_, p);
        return *this;
    }

    bool operator !()
    {
        return pthread_getspecific(key_)==NULL;
    }

    T* operator ->()
    {
        return static_cast<T*>(pthread_getspecific(key_));
    }

    T* get()
    {
        return static_cast<T*>(pthread_getspecific(key_));
    }
};
