#include"Server.h"
#include<iostream>
Server::Server(EventLoop * loop,int port):
    listenfd_(socket_bind_listen(port)),
    loop_(loop) 
{
    acceptchannel_=static_cast<std::shared_ptr<Channel>>(new Channel(loop,listenfd_));
    acceptchannel_->setCallRead(std::bind(&Server::acceptSock,this));
    setNoBlocking(listenfd_);
    loop_->getEPoll()->epoll_add(acceptchannel_);
}
void Server::start(){
    
}
void Server::acceptSock(){
    int acceptfd;
    
    while((acceptfd=accept(listenfd_,NULL,NULL))>=0){
        //std::cout<<"new socket"<<std::endl;
        if(acceptfd>MAXFDS) continue;
        sockfd=acceptfd;
        std::shared_ptr<Channel> request=static_cast<std::shared_ptr<Channel>>(new Channel(loop_,acceptfd));
        setNoBlocking(acceptfd);
        request->setCallRead(std::bind(&Server::Read,this));
        loop_->getEPoll()->epoll_add(request);

    }
    std::cout<<"ending socket"<<std::endl;
}
void Server::Read(){
    char buff[10];
    int n=read(sockfd,buff,10);
    buff[n]='\0';
    std::cout<<"hello"<<buff<<std::endl;
}