#include"Server.h"

#include<iostream>
Server::Server(EventLoop * loop,int port,int threadnum):
    listenfd_(socket_bind_listen(port)),
    loop_(loop),
    acceptchannel_(new Channel(loop_,listenfd_)),
    threadpoll_(loop_,threadnum)
{
    acceptchannel_->setCallRead(std::bind(&Server::acceptSock,this));
    setNoBlocking(listenfd_);
    loop_->getEPoll()->epoll_add(acceptchannel_);
}
void Server::start(){
    threadpoll_.start();
}
void* addFD(void* a){
    attr *at=static_cast<attr*>(a);
    int acceptfd=at->fd;
    std::shared_ptr<EventLoop> loop=at->loop;
    std::shared_ptr<HttpData> request(new HttpData(loop,acceptfd));        
    request->getChannel()->setHolder(request);
    return NULL;
}
void Server::acceptSock(){
    int acceptfd;
    while((acceptfd=accept(listenfd_,NULL,NULL))>=0){
        
        if(acceptfd>MAXFDS) continue;
        setNoBlocking(acceptfd);
        setNodely(acceptfd);
        std::shared_ptr<EventLoop> loop=threadpoll_.getNextEventloop();
        Functor f;
        f.fun=addFD;
        f.a.fd=acceptfd;
        f.a.loop=loop;
        {
            MutexGuard lock(loop->getMutex());
            loop->appendingFuntor(f);
        }
        loop->wakeup();        
    }
    //std::cout<<"new client"<<std::endl;
}
