#pragma once
#include<queue>
#include<sys/time.h>
#include<memory>
#include<string>
#include"HttpData.h"
#define timeout 30 
class TimerNode{
public:
    TimerNode(std::shared_ptr<HttpData> httpdata) 
            :httpdata_(httpdata)
    {
      struct timeval now;
      gettimeofday(&now,NULL);
      ExpiredTime_=now.tv_sec+timeout;
    }
    size_t getExpiredTime(){
        return ExpiredTime_;
    }
    void epoll_del(){
        httpdata_->expired();
    }
private:
    //HttpData* httpdata;
    std::shared_ptr<HttpData> httpdata_;
    size_t ExpiredTime_;//64位
};

typedef std::shared_ptr<TimerNode> SP_TimerNode;

struct cmp{
    bool operator()(SP_TimerNode a, SP_TimerNode b) const {
        return a->getExpiredTime()>b->getExpiredTime();
    }

};

class TimerHeap{
public: 
    TimerHeap()=default;
    void addTimer(SP_TimerNode& node){
        TimerQueue.push(node);
    }
    void addTimer(std::shared_ptr<HttpData> req){
        TimerQueue.push(static_cast<SP_TimerNode>(new TimerNode(req)));
    }
    void handleExpiredEvent(){
        struct timeval now;
        gettimeofday(&now,NULL);
        while(!TimerQueue.empty()){
           SP_TimerNode node=TimerQueue.top();
            if(node->getExpiredTime()<now.tv_sec)
                {
                    node->epoll_del();
                    TimerQueue.pop();
                }
            else break;
        }
    }
private:
    
    std::priority_queue<SP_TimerNode,std::deque<SP_TimerNode>,cmp> TimerQueue;
};