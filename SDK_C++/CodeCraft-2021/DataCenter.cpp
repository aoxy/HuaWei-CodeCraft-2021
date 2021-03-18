#include <fstream>
#include "DataCenter.h"

std::pair<int, char> DataCenter::deploy(ProtoVM pvm, int vid)
{

    if (0 == pvm.node())
    {
        if (servers0.empty())
            return std::pair<int, char>(-1, 'X');
        auto firsts = servers0.begin();
        // std::cout << "(" << firsts->acore << ","
        //           << firsts->aram << ","
        //           << firsts->bcore << ","
        //           << firsts->bram << ")" << std::endl;
        Server s(firsts);
        int res = s.deploy(pvm, vid);
        if (res < 0)
        {
            std::cout << "买服务器：(" << s.sid << ","
                      << s.acore << ","
                      << s.aram << ","
                      << s.bcore << ","
                      << s.bram << ")"
                      << pvm.core() << "," << pvm.ram() << "," << pvm.node() << std::endl;
            return std::pair<int, char>(-1, 'X');
        }
        std::multiset<Server, ServerCmp1>::iterator it = servers1.begin();
        for (it = servers1.begin(); it != servers1.end(); it++)
            if (it->sid == s.sid)
                break;
        if (it == servers1.end())
        {
            std::cout << "致命BUG" << std::endl;
            return std::pair<int, char>(-1, 'X');
        }
        if (res == 0)
        {
            servers0.erase(firsts);
            servers0.insert(s);
            servers1.erase(it);
            servers1.insert(s);
            vms.insert({vid, VM(vid, s.sid, pvm, 'A')});
            return std::pair<int, char>(s.sid, 'A');
        }
        else
        {
            servers0.erase(firsts);
            servers0.insert(s);
            servers1.erase(it);
            servers1.insert(s);
            vms.insert({vid, VM(vid, s.sid, pvm, 'B')});
            return std::pair<int, char>(s.sid, 'B');
        }
    }
    else
    {
        if (servers1.empty())
            return std::pair<int, char>(-1, 'X');
        auto firsts = servers1.begin();
        // std::cout << "(" << firsts->acore << ","
        //           << firsts->aram << ","
        //           << firsts->bcore << ","
        //           << firsts->bram << ")" << std::endl;
        Server s(firsts);
        int res = s.deploy(pvm, vid);
        if (res < 0)
        {
            std::cout << "买服务器：(" << s.sid << ","
                      << s.acore << ","
                      << s.aram << ","
                      << s.bcore << ","
                      << s.bram << ")"
                      << pvm.core() << "," << pvm.ram() << "," << pvm.node() << std::endl;
            return std::pair<int, char>(-1, 'X');
        }
        std::multiset<Server, ServerCmp0>::iterator it = servers0.begin();
        for (it = servers0.begin(); it != servers0.end(); it++)
            if (it->sid == s.sid)
                break;
        if (it == servers0.end())
        {
            std::cout << "致命BUG" << std::endl;
            return std::pair<int, char>(-1, 'X');
        }
        servers1.erase(firsts);
        servers1.insert(s);
        servers0.erase(it);
        servers0.insert(s);
        vms.insert({vid, VM(vid, s.sid, pvm, 'D')});
        return std::pair<int, char>(s.sid, 'D');
    }
}

std::pair<std::pair<int, char>, std::string> DataCenter::add(ProtoVM pvm, int vid)
{
    std::pair<int, char> res = deploy(pvm, vid);
    if (res.second == 'X')
    {
        purchase(maxServer);
        res = deploy(pvm, vid);
        return std::pair<std::pair<int, char>, std::string>(res, maxServer.model());
    }
    return std::pair<std::pair<int, char>, std::string>(res, "");
}

void DataCenter::del(int vid)
{
    VM vm = vms.find(vid)->second;
    std::multiset<Server, ServerCmp0>::iterator it0 = servers0.begin();
    std::multiset<Server, ServerCmp0>::iterator it1 = servers1.begin();
    for (it0 = servers0.begin(); it0 != servers0.end(); it0++)
        if (it0->sid == vm.sid)
            break;
    for (it1 = servers1.begin(); it1 != servers1.end(); it1++)
        if (it1->sid == vm.sid)
            break;
    if (it0 == servers0.end() || it1 == servers1.end())
    {
        std::cout << "致命BUG" << std::endl;
        return;
    }
    Server s(it0);
    s.del(vm);
    servers0.erase(it0);
    servers0.insert(s);
    servers1.erase(it1);
    servers1.insert(s);
    vms.erase(vid);
}

void DataCenter::printusage(std::string fname)
{
    std::ofstream fout;
    fout.open(fname);
    fout << "服务器ID"
         << ","
         << "核使用率"
         << ","
         << "内存使用率"
         << ","
         << "A核使用率"
         << ","
         << "A内存使用率"
         << ","
         << "B核使用率"
         << ","
         << "B内存使用率"
         << ","
         << "原有核"
         << ","
         << "原有内存"
         << ","
         << "使用A核"
         << ","
         << "使用A内存"
         << ","
         << "使用B核"
         << ","
         << "使用B内存" << std::endl;
    for (auto s : servers0)
    {
        double core = s.ps.core();
        double ram = s.ps.ram();
        double f1 = 1 - (s.acore + s.bcore) / core;
        double f2 = 1 - (s.aram + s.bram) / ram;
        double f3 = 1 - s.acore * 2 / core;
        double f4 = 1 - s.aram * 2 / ram;
        double f5 = 1 - s.bcore * 2 / core;
        double f6 = 1 - s.bram * 2 / ram;
        fout << s.sid << "," << f1 << "," << f2 << "," << f3 << "," << f4 << "," << f5 << "," << f6 << "," << core << "," << ram << "," << s.acore << "," << s.aram << "," << s.bcore << "," << s.bram << std::endl;
    }
}