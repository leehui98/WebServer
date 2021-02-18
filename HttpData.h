#pragma once
#include<memory>
#include<string>
class EventLoop;
class Channel;

class HttpData{
public:
    HttpData(EventLoop* loop,int fd);
    void expired();
    void handlRead();
    void handleWrite();
private:
    typedef std::shared_ptr<Channel> SP_Channel;
    SP_Channel channel_;
    EventLoop* loop_;
    std::string in;
    std::string out;
};