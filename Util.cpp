#include"Util.h"
#include<iostream>
int socket_bind_listen(int port){
    int listenfd;
    struct sockaddr_in sever_address;
    bzero(&sever_address,sizeof(sever_address));
    sever_address.sin_family = AF_INET;
    sever_address.sin_addr.s_addr = htons(INADDR_ANY);
    sever_address.sin_port = htons(port);
 
    listenfd = socket(AF_INET,SOCK_STREAM,0);
    assert(listenfd!=-1);
    int ret = bind(listenfd, (struct sockaddr*)&sever_address,sizeof(sever_address));
    assert(ret != -1);
 
    ret = listen(listenfd,20);
    assert(ret != -1);
   
    return listenfd;
}
int setNoBlocking(int fd){
    int flag=fcntl(fd,F_GETFL,0);
    if(flag==-1) return -1;
    
    flag|=O_NONBLOCK;
    int ret=fcntl(fd,F_SETFL,flag);
    //assert(ret!=-1);
    return ret;
}
void setNodely(int fd){//关闭Negal算法
    int flag=1;
    int ret=setsockopt(fd,IPPROTO_TCP,TCP_NODELAY,(char*)&flag,sizeof flag);
    assert(ret!=-1);
}
int geteventfd(){
    int evtfd=eventfd(0,EFD_NONBLOCK|EFD_CLOEXEC);
    assert(evtfd>=0);
    return evtfd;
}
int readn(int fd,std::string &buff,int size){
    int read_size=0;
    char readbuff[MaxBuff];
    while(read_size<size){
        int n=read(fd,readbuff,size);
        if(n<0) break;
        else if(n==0) return 0;
        else if(n>0) read_size+=n;
        
        size-=n;
        buff+=std::string(readbuff,readbuff+n);
    }
    return read_size;

}
int readn(int fd,std::string &in){
    char buff[MaxBuff];
    int size=0;
    while(true){
        int n=read(fd,buff,MaxBuff);
        if(n<=0) return size;
        else if(n>0) size+=n;
        in+=std::string(buff,buff+n);
    }
    return size;
}
int writen(int fd,std::string &buff){
    int size=buff.size();
    int write_size=0;
    const char* ptr=buff.c_str();
    while(write_size<size){
        int n=write(fd,ptr+write_size,size);
        if(n<0) break;
        else if(n==0) return 0;
        else if(n>0) write_size+=n;
        size-=write_size;
    }
    return write_size;
}
int writen(int fd,char* buff,int size){
    int write_size=0;
    const char* ptr=buff;
    while(write_size<size){
        int n=write(fd,ptr+write_size,size);
        if(n<0) break;
        else if(n==0) return 0;
        else if(n>0) write_size+=n;
        size-=write_size;
    }
    return write_size;
}
int ShutdownWR(int fd){
    int ret=shutdown(fd,SHUT_WR);
    assert(ret!=-1);
    return ret;
}
int ShutdwonRDWR(int fd){
        int ret=shutdown(fd,SHUT_RDWR);
        assert(ret!=-1);
        return ret;
}