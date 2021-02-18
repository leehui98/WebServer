#pragma once
#include<functional>
#include<vector>

#include"EPoller.h"
#include"Channel.h"
#include"Util.h"
class EventLoop{
public:
    EventLoop();
    typedef std::function<void()> callback;
    void loop();
    EPoller* getEPoll(){return poller_;}
    void wakeup();
private:
    EPoller* poller_;
    int wakeupfd_;
};