#pragma once
#include"nocopyable.h"
#include"EventLoop.h"
#include"Util.h"
#include"Channel.h"
#include"HttpData.h"
#include"ThreadEventLoopPoll.h"
#include"Mutex.h"
class Server:nocopyable{
public:
    Server(EventLoop *loop,int port,int threadnum);
    void start();
    void sent();
    void onRequest();
    void acceptSock();
    void Read();
    static void* add2epoll(void* a);
private:
    std::shared_ptr<EventLoop> loop_;
    int listenfd_;
    std::shared_ptr<Channel> acceptchannel_;
    static const int MAXFDS = 10000;
    ThreadEventLoopPoll threadpoll_;//线程池
    
};