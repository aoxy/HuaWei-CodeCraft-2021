#ifndef SERVER_H_
#define SERVER_H_

#define MAGIC_FACTOR 1.2

#include <unordered_map>
#include "ProtoServer.h"
#include "Request.h"
#include "VM.h"

class Server
{
private:
    ProtoServer &ps;
    int acore; //A节点可用CPU数量
    int aram;  //A节点可用内存数量
    int bcore; //B节点可用CPU数量
    int bram;  //B节点可用内存数量
    int sid;
    std::unordered_map<int, VM> vms; //部署在该台服务器上的虚拟机

public:
    Server(ProtoServer &ps, int sid) : ps(ps), sid(sid)//ProtoVM pvm = VMType.find(request.model())->second;
    {
        acore = bcore = ps.core() >> 1;
        aram = bram = ps.ram() >> 1;
    }
    bool operator<(const Server &that) const
    {
        return (MAGIC_FACTOR * (acore + bcore) + aram + bram) < (MAGIC_FACTOR * (that.acore + that.bcore) + that.aram + that.bram); //剩余资源多的排前面
    }
    bool AgtB() const //A大于B
    {
        return (MAGIC_FACTOR * acore + aram) > (MAGIC_FACTOR * bcore + bram); //剩余资源多的排前面
    }
    /**
     * @return (-1,部署失败),(1,单节点A部署成功)，(1,单节点B部署成功),(2,双节点部署成功)
     */
    int add(ProtoVM &pvm,int vid);
};

#endif