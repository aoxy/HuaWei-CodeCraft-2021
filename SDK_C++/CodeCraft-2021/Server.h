#ifndef SERVER_H_
#define SERVER_H_

#include <unordered_map>
#include <set>
#include "ProtoServer.h"
#include "Request.h"
#include "VM.h"

class Server
{
public:
    ProtoServer ps;
    int acore; //A节点可用CPU数量
    int aram;  //A节点可用内存数量
    int bcore; //B节点可用CPU数量
    int bram;  //B节点可用内存数量
    int sid;
    std::unordered_map<int, VM> svms; //部署在该台服务器上的虚拟机

    Server(ProtoServer ps, int sid)
    {
        this->ps = ps;
        this->sid = sid;
        acore = bcore = ps.core() >> 1;
        aram = bram = ps.ram() >> 1;
        svms = std::unordered_map<int, VM>();
    }
    Server(const Server &that) : ps(that.ps)
    {
        acore = that.acore;
        bcore = that.bcore;
        aram = that.aram;
        bram = that.bram;
        sid = that.sid;
        svms = std::unordered_map<int, VM>(that.svms);
    }
    Server(const std::multiset<Server>::iterator it)
    {
        ps = it->ps;
        acore = it->acore;
        bcore = it->bcore;
        aram = it->aram;
        bram = it->bram;
        sid = it->sid;
        svms = it->svms;
    }
    // bool operator<(const Server &that) const
    // {
    //     return (MAGIC_FACTOR * (acore + bcore) + aram + bram) > (MAGIC_FACTOR * (that.acore + that.bcore) + that.aram + that.bram); //剩余资源多的排前面
    // }
    // bool operator==(const Server &that) const
    // {
    //     return sid == that.sid;
    // }
    bool AgtB() const //A大于B
    {
        return (MAGIC_FACTOR * acore + aram) >= (MAGIC_FACTOR * bcore + bram); //剩余资源多的排前面
    }
    double match(ProtoVM pvm) const;
    /**
     * @return (-1,部署失败),(0,单节点A部署成功)，(1,单节点B部署成功),(2,双节点部署成功)
     */
    int deploy(ProtoVM pvm, int vid);
    void del(VM vm);
};

#endif