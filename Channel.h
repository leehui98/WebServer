#pragma once
#include"nocopyable.h"
#include<string.h>
#include<sys/epoll.h>
#include<memory>
#include<functional>

class EventLoop;
class HttpData;
typedef std::function<void()> CallBack;
class Channel:nocopyable{
public:
    Channel(EventLoop* loop);
    Channel(EventLoop* loop,int fd);
    void setHolder(std::shared_ptr<HttpData> holder);
    void handleEvent();
    __uint32_t get_event(){return event_;}
    void expired();
    std::shared_ptr<HttpData> getHolder();
    void setRevent(const __uint32_t &e);
    void setCallRead(CallBack &&cb);
    void setCallWrite(CallBack &&cb);
    
    int getFd(){return fd_;}
private:
    int fd_;
    CallBack callRead_;
    CallBack callWrite_;
    __uint32_t event_;//注册的事件
    EventLoop* loop_;
    
    __uint32_t revent_;//返回的事件
    std::shared_ptr<HttpData> holder_;//方便找到持有Channel的对象
};