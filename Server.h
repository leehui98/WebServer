#pragma once
#include"nocopyable.h"
#include"EventLoop.h"
#include"Util.h"
#include"Channel.h"
class Server:nocopyable{
public:
    Server(EventLoop *loop,int port);
    void start();
    void sent();
    void onRequest();
    void acceptSock();
    void Read();
private:
int sockfd;
    EventLoop* loop_;
    int listenfd_;
    std::shared_ptr<Channel> acceptchannel_;
    static const int MAXFDS = 10000;
   // ThreadEventLoopPoll threadpoll;//线程池
};