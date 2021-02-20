#pragma once
#include<memory>
#include<string>
#include<unordered_map>
#include<iostream>
class EventLoop;
class Channel;

enum ProcessState{
    STATE_PARSE_URI=1,//下一步解析请求行
    STATE_PARSE_HEADERS,//解析请求头部
    STATE_RECV_BODY,//解析请求体
    STATE_ANALYSIS,
    STATE_FINFIS//解析完成
};
enum ParseState{
    Parse_Again=1,
    Parse_success,
    Parse_error
};
enum Method{
    METHOD_POST=1,
    METHOD_GET,
};
struct HEAD{
    std::unordered_map<std::string,std::string> memo;
};
class HttpData{
public:
    HttpData(std::shared_ptr<EventLoop> loop,int fd);
    void expired();
    void handlRead();
    void handleWrite();
    std::shared_ptr<Channel> getChannel(){return channel_;}
    void Read();
    ParseState parseUrl();
    ParseState parseHead();
    void Write();
private:
    int fd_;
    typedef std::shared_ptr<Channel> SP_Channel;
    SP_Channel channel_;
    std::shared_ptr<EventLoop> loop_;
    ProcessState state_;
    Method method_;
    std::string filename_;
    std::string HTTP_ver_;
    HEAD head_;
    std::string in;
    std::string out;
};