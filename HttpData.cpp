#include"HttpData.h"
#include"EventLoop.h"
#include<iostream>
HttpData::HttpData(std::shared_ptr<EventLoop> loop,int fd):
                    loop_(loop),channel_(new Channel(loop,fd)),Parse_success(false)
{
        fd_=fd;
        channel_->setCallRead(std::bind(&HttpData::Read,this));
        channel_->setCallWrite(std::bind(&HttpData::Write,this));
        loop_->getEPoll()->epoll_add(channel_);
}
void HttpData::expired(){
        channel_->expired();
}
void HttpData::Read(){
        std::cout<<channel_->getFd()<<":";
        in.clear();
        int n=readn(channel_->getFd(),in);
        if(n==0){
                return;
        }
        std::cout<<in<<std::endl;
        Parse_success=true;
        if(Parse_success){
        out="hello";
        __uint32_t e=EPOLLET|EPOLLIN|EPOLLOUT;
        channel_->setEvent(e);
        loop_->getEPoll()->epoll_update(channel_);
        }
}
void HttpData::Write(){
        if(out.size()!=0)
                {
                        int n=writen(channel_->getFd(),out);
                        out.erase(out.begin(),out.begin()+n);
                }
        else {
                __uint32_t e=EPOLLET|EPOLLIN;
                channel_->setEvent(e);
                loop_->getEPoll()->epoll_update(channel_);
        }
}