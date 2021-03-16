#include "DataCenter.h"

std::pair<int, char> DataCenter::deploy(ProtoVM pvm, int vid)
{
    // std::cout << vms.size() << "size-----" << std::endl;
    if (servers.empty())
        return std::pair<int, char>(-1, 'X');
    auto firsts = servers.begin();
    Server s(*firsts);
    int res = s.deploy(pvm, vid);
    switch (res)
    {
    case 0:
    {
        update(s, firsts);
        vms.insert({vid, VM(vid, s.sid, pvm, 'A')});
        return std::pair<int, char>(s.sid, 'A');
        break;
    }
    case 1:
    {
        update(s, firsts);
        vms.insert({vid, VM(vid, s.sid, pvm, 'B')});
        return std::pair<int, char>(s.sid, 'B');
        break;
    }
    case 2:
    {
        update(s, firsts);
        VM vm1(vid, s.sid, pvm, 'D');
        vms.insert({vid, vm1});
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
    // std::cout << "===============" << std::endl;
    // auto it = vms.begin();
    // for (auto it = vms.begin(); it != vms.end(); it++)
    //     if (it->first == vid)
    //         break;

    // VM vm = it->second;
    // // std::cout << it->first << std::endl;
    // std::cout << "===============" << std::endl;
    // std::cout << vid << vm.pvm.model() << std::endl;
    // auto it = servers.find(s5);
    // Server s = *it;
    // s.a = 1145;
    // servers.erase(it);
    // servers.insert(s);

    // std::cout << "Here-0=" << vid << std::endl;
    // VM vm = vms.find(vid)->second;
    // std::cout<<vm.pvm;
    // std::cout << "Here-1=" << vm.server.acore << std::endl;
    std::set<Server>::iterator it;
    for (it = servers.begin(); it != servers.end(); it++)
        if (it->sid == vm.sid)
            break;

    Server s(*it);
    s.del(vm);
    servers.erase(it);
    servers.insert(s);
    vms.erase(vid);
}

void DataCenter::update(Server &n, std::set<Server>::iterator o)
{
    servers.erase(o);
    servers.insert(n);
}

void DataCenter::print()
{
    for (auto it = vms.begin(); it != vms.end(); it++)

        std::cout << it->first << "||" << it->second.pvm << std::endl;
}