#pragma once
#include"nocopyable.h"
#include<vector>
#include<sys/epoll.h>
#include<memory>
#include"Channel.h"
#include"Timer.h"
typedef std::shared_ptr<Channel> SP_Channel;
typedef std::shared_ptr<HttpData> SP_HttpData;
class EPoller{
public:
    EPoller();
    void epoll_add(SP_Channel request);//add fd
    void epoll_delete(SP_Channel request);//delete fd
    void epoll_update(SP_Channel request);//update events
    void getActive();
    void handleExpired();
    std::vector<SP_Channel> poll();

private:
    TimerHeap timermanger_;
    int epfd_;
    static const int MAXFDS=10000;
    epoll_event events_[MAXFDS];//active events
    SP_Channel fd2chan_[MAXFDS];
    SP_HttpData fd2http_[MAXFDS];
};