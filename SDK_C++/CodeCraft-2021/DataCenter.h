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

public:

    void purchase(ProtoServer &ps, int sid)
    {
        Server s(ps, sid);
        //servers.push(s);
    }

    void add(Request r);
    void del(Request r);

public:
    DataCenter() {}
};

#endif