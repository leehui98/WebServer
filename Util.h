#pragma once
#include<fcntl.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/tcp.h>
#include<string>
#include<string.h>
#include<assert.h>
#include<unistd.h>
#include<sys/eventfd.h>

#define MaxBuff 64*1024
int  socket_bind_listen(int port);
int setNoBlocking(int fd);
void setNodely(int fd);//关闭Negal算法
int readn(int fd,std::string &buff);
int writen(int fd,std::string &buff);
int writen(int fd,char* buff,int size);
int geteventfd();