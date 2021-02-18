#include"HttpData.h"
#include"EventLoop.h"

HttpData::HttpData(EventLoop* loop,int fd):
                    loop_(loop),channel_(new Channel(loop,fd))
{

}
void HttpData::expired(){
        channel_->expired();
}
//发送完毕，关闭EPOLLOUT