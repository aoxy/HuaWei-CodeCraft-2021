#ifndef DATA_CENTER_H_
#define DATA_CENTER_H_

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_map>
#include "Util.h"
#include "ProtoServer.h"
#include "ProtoVM.h"
#include "DataCenter.h"
#include "Server.h"
#include "Request.h"
#include "VM.h"

struct ServerCmp0
{
    bool operator()(const Server &s1, const Server &s2) const
    {
        int smax1 = MAX(MAGIC_FACTOR * s1.acore + s1.aram, MAGIC_FACTOR * s1.bcore + s1.bram);
        int smax2 = MAX(MAGIC_FACTOR * s2.acore + s2.aram, MAGIC_FACTOR * s2.bcore + s2.bram);
        return smax1 > smax2;
    }
};

struct ServerCmp1
{
    bool operator()(const Server &s1, const Server &s2) const
    {
        int smin1 = MAX(MAGIC_FACTOR * s1.acore + s1.aram, MAGIC_FACTOR * s1.bcore + s1.bram);
        int smin2 = MAX(MAGIC_FACTOR * s2.acore + s2.aram, MAGIC_FACTOR * s2.bcore + s2.bram);
        return smin1 > smin2;
    }
};

class DataCenter
{
private:
    std::multiset<Server, ServerCmp0> servers0; //数据中心购买了的所有服务器（给单节点用）
    std::multiset<Server, ServerCmp1> servers1; //数据中心购买了的所有服务器(给双节点用)
    std::unordered_map<int, VM> vms;            //数据中心部署了的所有虚拟机
    int _scount;
    ProtoServer maxServer;

public:
    DataCenter(ProtoServer maxServer) : _scount(0), maxServer(maxServer) {}
    void purchase(ProtoServer ps)
    {

        Server s(ps, _scount++);
        servers0.insert(s);
        servers1.insert(s);
    }
    int scount() { return _scount; }
    std::pair<int, char> deploy(ProtoVM pvm, int vid);
    std::pair<std::pair<int, char>, std::string> add(ProtoVM pvm, int vid);
    void del(int vid);
    void printusage(std::string fname);
};

#endif