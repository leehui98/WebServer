#include"HttpData.h"
#include"EventLoop.h"
#include"Util.h"
#include<iostream>
#include<fstream>
HttpData::HttpData(std::shared_ptr<EventLoop> loop,int fd):
                    loop_(loop),channel_(new Channel(loop,fd))
                    ,state_(STATE_PARSE_URI),fd_(fd)
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
        //std::cout<<channel_->getFd()<<":";
        in.clear();
        int n=readn(channel_->getFd(),in);
        //std::cout<<in<<std::endl;
        if(n==0){
                ShutdwonRDWR(fd_);
                return;
        }

        do{
        if(state_==STATE_PARSE_URI){
                ParseState flag=parseUrl();

                if(flag==Parse_Again) break;
                else if(flag==Parse_success) {
                        state_=STATE_PARSE_HEADERS;
                }
                else if(flag==Parse_error){
                        ShutdwonRDWR(fd_);
                        return ;
                }
        }
        if(state_==STATE_PARSE_HEADERS){
                ParseState flag=parseHead();
                if(flag==Parse_Again) break;
                else if(flag==Parse_success) {
                        state_=STATE_RECV_BODY;
                }
                else if(flag==Parse_error){
                        ShutdwonRDWR(fd_);
                        return ;
                }
        }
        if(state_==STATE_RECV_BODY){
                state_=STATE_FINFIS;
        }
        }while(false);
        if(access(filename_.c_str(),R_OK)==0)
                {
                        std::ifstream fin{filename_};
                        out="HTTP/1.1 200 OK\r\n\r\n";
                        std::string content;
                        while(getline(fin,content)){
                        out+=content+"\r\n";
                        }
                        out+="\r\n";
                        //std::cout<<out<<std::endl;
                }
        else 
                {
                       out="HTTP/1.1 404 bad\r\n\r\n<html>404 error!<br>The source not found!<br>The source dir is : ";
                       out+=filename_+"</html>\r\n\r\n";
                }

        if(state_=STATE_FINFIS){
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
         //std::cout<<"send end"<<std::endl;
         ShutdownWR(channel_->getFd());
}
ParseState HttpData::parseUrl(){
        int pos=in.find("\r\n");
        if(pos<0) return Parse_Again;
        
        std::string request_line=in.substr(0,pos);
        if(in.size()>pos+1)
                in=in.substr(pos+2);
        else in.clear();

        int posGet=request_line.find("GET");
        int posPost=request_line.find("POST");
        if(posGet>=0) {
                method_=METHOD_GET;
                pos=posGet;
        }
        else if(posPost>=0) {
                method_=METHOD_POST;
                pos=posPost;
        }
        else return Parse_error;
                
        pos=request_line.find('/');
        int _pos=request_line.find(' ',pos);
        filename_=request_line.substr(pos+1,_pos-pos-1);
        
        if(filename_=="") filename_="index.html";
        HTTP_ver_=request_line.substr(_pos,request_line.size()-_pos);
        return Parse_success;
};
ParseState HttpData::parseHead(){
        while(in.find("\r\n")!=0){
                int pos=in.find("\r\n");
                if(pos<0) return Parse_Again;
                std::string head_line=in.substr(0,pos);
                in=in.substr(pos+2);
                int _pos=head_line.find(": ");
                if(_pos<0) {
                        return Parse_error;

                }
                std::string head=head_line.substr(0,_pos);
                std::string content=head_line.substr(_pos+2);
                head_.memo[head]=content;
                //std::cout<<head_line<<std::endl;
                //std::cout<<head<<std::endl;
                //std::cout<<content<<std::endl;
                
                
        }
        {
                in=in.substr(2);
                return Parse_success;
        }
       
}