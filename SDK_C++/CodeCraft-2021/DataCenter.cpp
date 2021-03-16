#include "DataCenter.h"

std::pair<int, char> DataCenter::deploy(ProtoVM &pvm, int vid)
{
    if (servers.empty())
        return std::pair<int, char>(-1, 'X');
    Server s = servers.top();
    switch (s.deploy(pvm, vid))
    {
    case 0:
    {
        servers.pop();
        servers.push(s);
        return std::pair<int, char>(s.sid(), 'A');
        break;
    }
    case 1:
    {
        servers.pop();
        servers.push(s);
        return std::pair<int, char>(s.sid(), 'B');
        break;
    }
    case 2:
    {
        servers.pop();
        servers.push(s);
        return std::pair<int, char>(s.sid(), 'D');
        break;
    }
    default:
    {
        return std::pair<int, char>(-1, 'X');
        break;
    }
    }
}

std::pair<std::pair<int, char>, std::string> DataCenter::add(ProtoVM &pvm, int vid)
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
    Server s(servers.top());
    s.del(vid);
    servers.pop();
    servers.push(s);
}