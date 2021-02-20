#include"Channel.h"
#include"EventLoop.h"

Channel::Channel(std::shared_ptr<EventLoop> loop,int fd):loop_(loop)
{
    
    bzero(&event_,sizeof(event_));
    fd_=fd;
    event_=EPOLLIN|EPOLLET;
    
}
void Channel::expired(){
    loop_->getEPoll()->epoll_delete(static_cast<std::shared_ptr<Channel>>(this));
}
void Channel::setHolder(std::shared_ptr<HttpData> holder) 
{
    holder_=holder;
}
std::shared_ptr<HttpData> Channel::getHolder(){
    return holder_;
}
void Channel::setCallRead(CallBack &&cb){
    callRead_=cb;
}
void Channel::setCallWrite(CallBack &&cb){
    callWrite_=cb;
}
void Channel::setRevent(const __uint32_t &e){
    revent_=e;
}
void Channel::setEvent(const __uint32_t &e){
    event_=e;
}
void Channel::handleEvent(){
    if(revent_&EPOLLIN){
        callRead_();
    }
    if(revent_&EPOLLOUT){
        callWrite_();
    }
}