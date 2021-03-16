#ifndef DATA_CENTER_H_
#define DATA_CENTER_H_

#include <iostream>
#include <vector>
#include <string>
#include <set>
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
    std::multiset<Server> servers;   //数据中心购买了的所有服务器
    std::unordered_map<int, VM> vms; //数据中心部署了的所有虚拟机
    int _scount;
    ProtoServer maxServer;

public:
    DataCenter(ProtoServer maxServer) : _scount(0), maxServer(maxServer) {}
    void purchase(ProtoServer ps)
    {
        Server s(ps, _scount++);
        servers.insert(s);
    }
    int scount() { return _scount; }
    std::pair<int, char> deploy(ProtoVM pvm, int vid);
    std::pair<std::pair<int, char>, std::string> add(ProtoVM pvm, int vid);
    void del(int vid);
    void update(Server *n, std::multiset<Server>::iterator o);
    void print();
    void print2();
};

#endif