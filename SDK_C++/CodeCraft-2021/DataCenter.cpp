#include "DataCenter.h"

std::pair<int, char> DataCenter::deploy(ProtoVM pvm, int vid)
{
    // std::cout << vms.size() << "size-----" << std::endl;
    if (servers.empty())
        return std::pair<int, char>(-1, 'X');
    auto firsts = servers.begin();
    Server s(firsts);
    // if (s.sid == 54)
    // {
    //     std::cout << "54存在感" << vid << std::endl;
    // }
    // std::cout << s->acore << "acore" << s->bcore << "bcore" << vid << std::endl;
    int res = s.deploy(pvm, vid);
    // std::cout << s->acore << "acore" << s->bcore << "bcore" << vid << std::endl;
    switch (res)
    {
    case 0:
    {
        // std::cout << servers.size() << "size" << vid << std::endl;
        servers.erase(firsts);
        // std::cout << servers.size() << "size" << vid << std::endl;
        // std::cout << s->sid << "sid" << vid << std::endl;
        servers.insert(s);
        vms.insert({vid, VM(vid, s.sid, pvm, 'A')});
        return std::pair<int, char>(s.sid, 'A');
        break;
    }
    case 1:
    {
        // std::cout << servers.size() << "size" << vid << std::endl;
        servers.erase(firsts);
        // std::cout << servers.size() << "size" << vid << std::endl;
        // std::cout << s->sid << "sid" << vid << std::endl;
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
    // std::cout << "Here-1===" << std::endl;
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
    // std::cout << "Here-2===" << std::endl;
    std::multiset<Server>::iterator it = servers.begin();
    // std::cout << "Here-3===" << std::endl;
    // if (vm.sid == 54)
    // {
    //     for (it = servers.begin(); it != servers.end(); it++)
    //         std::cout << it->sid << ":::";
    // }
    for (it = servers.begin(); it != servers.end(); it++)
        if (it->sid == vm.sid)
            break;
    // std::cout << "Here-4===" << std::endl;
    if (it == servers.end())
    {
        std::cout << "===============" << vid << "|||" << vm.sid << std::endl;
        std::cout << "没找到 size:" << servers.size() << std::endl;
        return;
    }
    // std::cout << "Here-5===" << std::endl;
    Server s(it);
    // std::cout << "Here-6===" << std::endl;
    // auto it1 = servers.find(s);
    // std::cout << "===============" << vid << "|||" << it->sid << std::endl;

    s.del(vm);
    // update(s, it);
    servers.erase(it);
    servers.insert(s);
    vms.erase(vid);
}

void DataCenter::update(Server *n, std::multiset<Server>::iterator o)
{
    servers.erase(o);
    // delete &*o;
    servers.insert(*n);
}

void DataCenter::print()
{
    for (auto it = vms.begin(); it != vms.end(); it++)
        std::cout << it->first << "||" << it->second.pvm << std::endl;
}
bool check(Server s);
void DataCenter::print2()
{
    for (auto it = servers.begin(); it != servers.end(); it++)
        if (!check(*it))
            std::cout << "分配错误";
    // auto it = servers.begin();
    // std::cout << "sid: " << it->sid << std::endl;
    // std::cout << it->ps << std::endl;
    // std::cout << it->acore << std::endl;
    // std::cout << it->bcore << std::endl;
    // std::cout << it->aram << std::endl;
    // std::cout << it->bram << std::endl;
    // std::cout << "size: " << it->svms.size() << std::endl;
    // for (auto i = it->svms.begin(); i != it->svms.end(); i++)
    //     std::cout << i->first << "||" << i->second.pvm << "||" << i->second.node << std::endl;
}

bool check(Server s)
{
    ProtoServer ps = s.ps;
    int uacore = 0;
    int ubcore = 0;
    int uaram = 0;
    int ubram = 0;
    for (auto i = s.svms.begin(); i != s.svms.end(); i++)
    {
        if (i->second.node == 'D')
        {
            uacore += i->second.pvm.core() >> 1;
            ubcore += i->second.pvm.core() >> 1;
            uaram += i->second.pvm.ram() >> 1;
            ubram += i->second.pvm.ram() >> 1;
        }
        else if (i->second.node == 'A')
        {
            uacore += i->second.pvm.core();
            uaram += i->second.pvm.ram();
        }
        else if (i->second.node == 'B')
        {
            ubcore += i->second.pvm.core();
            ubram += i->second.pvm.ram();
        }
        else
        {
            std::cout << "严重错误";
        }
    }
    int hcore = ps.core() >> 1;
    int hram = ps.ram() >> 1;
    return (hcore == s.acore + uacore && hcore == s.bcore + ubcore && hram == s.aram + uaram && hram == s.bram + ubram);
}