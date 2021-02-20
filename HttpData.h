#pragma once
#include<memory>
#include<string>
class EventLoop;
class Channel;

class HttpData{
public:
    HttpData(std::shared_ptr<EventLoop> loop,int fd);
    void expired();
    void handlRead();
    void handleWrite();
    std::shared_ptr<Channel> getChannel(){return channel_;}
    void Read();
    void Write();
private:
    int fd_;
    typedef std::shared_ptr<Channel> SP_Channel;
    SP_Channel channel_;
    std::shared_ptr<EventLoop> loop_;
    std::string in;
    std::string out;
    bool Parse_success;
};