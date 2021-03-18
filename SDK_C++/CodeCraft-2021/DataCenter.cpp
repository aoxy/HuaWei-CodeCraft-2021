#include "DataCenter.h"

std::pair<int, char> DataCenter::deploy(ProtoVM pvm, int vid)
{
    if (servers.empty())
        return std::pair<int, char>(-1, 'X');
    auto firsts = servers.begin();
    Server s(firsts);
    int res = s.deploy(pvm, vid);
    switch (res)
    {
    case 0:
    {
        servers.erase(firsts);
        servers.insert(s);
        vms.insert({vid, VM(vid, s.sid, pvm, 'A')});
        return std::pair<int, char>(s.sid, 'A');
        break;
    }
    case 1:
    {
        servers.erase(firsts);
        servers.insert(s);
        vms.insert({vid, VM(vid, s.sid, pvm, 'B')});
        return std::pair<int, char>(s.sid, 'B');
        break;
    }
    case 2:
    {
        servers.erase(firsts);
        servers.insert(s);
        vms.insert({vid, VM(vid, s.sid, pvm, 'D')});
        return std::pair<int, char>(s.sid, 'D');
        break;
    }
    default:
    {
        return std::pair<int, char>(-1, 'X');
        break;
    }
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
    std::multiset<Server>::iterator it = servers.begin();
    for (it = servers.begin(); it != servers.end(); it++)
        if (it->sid == vm.sid)
            break;
    if (it == servers.end())
        return;
    Server s(it);
    s.del(vm);
    servers.erase(it);
    servers.insert(s);
    vms.erase(vid);
}

int DataCenter::daylyCost()
{
    int sum = 0;
    for(auto a : servers)
    {
        sum += a.ps.cost();
    }
    return(sum);
}
