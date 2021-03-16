#ifndef DATA_CENTER_H_
#define DATA_CENTER_H_

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include "ProtoServer.h"
#include "ProtoVM.h"
#include "DataCenter.h"
#include "Server.h"
#include "Request.h"
#include "VM.h"

class DataCenter
{
private:
    std::priority_queue<Server> servers; //数据中心购买了的所有服务器
    std::unordered_map<int, VM> vms;     //数据中心部署了的所有虚拟机
    int scount;
    ProtoServer &maxServer;

public:
    DataCenter(ProtoServer &maxServer) : scount(0), maxServer(maxServer) {}
    void purchase(ProtoServer &ps)
    {
        Server s(ps, scount++);
        servers.push(s);
    }

    std::pair<int, char> deploy(ProtoVM &pvm, int vid);
    std::pair<int, char> add(ProtoVM &pvm, int vid);
    void del(int vid);
};

#endif