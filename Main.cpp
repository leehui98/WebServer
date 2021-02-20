#include<iostream>
#include<string.h>
#include<getopt.h>
#include<unistd.h>
#include"EventLoop.h"
#include"Server.h"
#include"Logging.h"
#include<sys/time.h>
using namespace std;


int main(int argc,char* argv[]){
    int port=2333;
    int opt;
    const char *str="p";
    while((opt=getopt(argc,argv,str))!=-1){
        switch(opt){
            case 'p':{
                port=atoi(optarg);
                break;
            }
        }
    }
    Log<<"start WebServer";
    EventLoop loop_;
    Server server_(&loop_,port,4);
    server_.start();
    loop_.loop();
    return 0;
}