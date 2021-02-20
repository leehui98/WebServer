#include"EPoller.h"
#include<assert.h>
#include<iostream>
#include<sys/socket.h>

EPoller::EPoller(){
    epfd_=epoll_create1(EPOLL_CLOEXEC);
    assert(epfd_>0);
}
void EPoller::epoll_add(SP_Channel request){//add fd

    int fd=request->getFd();
    if(fd>=MAXFDS) return;
    fd2chan_[fd]=request;
    epoll_event ev;
    ev.data.fd=fd;
    ev.events=request->get_event();
    int ret=epoll_ctl(epfd_,EPOLL_CTL_ADD,fd,&(ev));
    assert(ret!=-1);
    timermanger_.addTimer(request->getHolder());
}
void EPoller::epoll_delete(SP_Channel request){//delete fd
    
    int fd=request->getFd();
    if(fd>=MAXFDS) return;
    
    epoll_event ev;
    ev.data.fd=fd;
    ev.events=request->get_event();
    int ret=epoll_ctl(epfd_,EPOLL_CTL_DEL,fd,&(ev));
    assert(ret!=-1);

    fd2chan_[fd].reset();
   // close(fd);
    
}
void EPoller::epoll_update(SP_Channel request){//update timer
    int fd=request->getFd();
    if(fd>=MAXFDS) return;
    
    epoll_event ev;
    ev.data.fd=fd;
    ev.events=request->get_event();
    int ret=epoll_ctl(epfd_,EPOLL_CTL_MOD,fd,&(ev));
    assert(ret!=-1);

}

std::vector<SP_Channel> EPoller::poll(){
   std::vector<SP_Channel> active;
   int ret_num=epoll_wait(epfd_,&(events_[0]),MAXFDS,-1);
       
   for(int i=0;i<ret_num;i++){
       int fd=events_[i].data.fd;
       fd2chan_[fd]->setRevent(events_[i].events);
       active.push_back(fd2chan_[fd]);
   }
   return active;
}