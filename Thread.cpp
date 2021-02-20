#include"Thread.h"
Thread::Thread(Fun fun):
    fun_(fun)
{

}

void Thread::start(){
    pthread_create(&pthreadID_,NULL,threadfun,this);
}
void* Thread::threadfun(void* attr){
    Thread *t=static_cast<Thread*>(attr);
    t->fun_();
    return NULL;
}