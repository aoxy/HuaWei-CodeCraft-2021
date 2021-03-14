#ifndef PURCHASE_SERVER_H_
#define PURCHASE_SERVER_H_

#include <iostream>
#include <vector>
#include <string>
#include "ProtoServer.h"
#include "ProtoVM.h"
/**
 * 描述一种类型的虚拟机，数据格式为：(型号,CPU核数, 内存大小, 是否双节点部署)。
 * 是否双节点部署用0和1表示，0 表示单节点部署，1 表示双节点部署。
 * 例如(s3.small.1,1, 1, 0)表示一种虚拟机类型，其型号为s3.small.1，所需 CPU核数为1，所需内存为 1G，单节点部署；
 * (c3.8xlarge.2, 32,64, 1)表示一种虚拟机类型，其型号为 c3.8xlarge.2，所需 CPU核数为32，所需内存为64G，双节点部署。
 * CPU核数，内存大小均为正整数。对于每种类型的虚拟机，数据集保证至少存在一种服务器可以容纳。
 * 虚拟机型号长度不超过20，仅由数字，大小写英文字符和'.'构成。
 */
class PurchasedServer
{
private:
    struct Server
    {
        ProtoServer &pserver;
        int acore; //A节点可用CPU数量
        int aram;  //A节点可用内存数量
        int bcore; //B节点可用CPU数量
        int bram;  //B节点可用内存数量
        Server(ProtoServer &ps) : pserver(ps)
        {
            acore = bcore = ps.core() >> 1;
            aram = bram = ps.ram() >> 1;
        }
        bool deploy(ProtoVM &pvm)
        {
            if (pvm.node() == 0)
            {
                if (pvm.core()) //TODO: 单节点部署
            }
            else
            {
                int halfcore = pvm.core() >> 1;
                int halfram = pvm.ram() >> 1;
                if (halfcore <= this->acore && halfcore <= this->bcore && halfram <= this->bram && halfram <= this->bram)
                {
                    this->acore -= halfcore;
                    this->bcore -= halfcore;
                    this->aram -= halfram;
                    this->bram -= halfram;
                }
                else
                    return false;
            }
        }
    };
    void purchase(ProtoServer ps) {}
    std::vector<Server> servers;
    int _core;
    int _ram;
    int _node;

public:
    ProtoVM() {}
    ProtoVM(std::string model, int core, int ram, int node)
        : _model(model), _core(core), _ram(ram), _node(node) {}
    friend std::ostream &operator<<(std::ostream &os, const ProtoVM &m);
    friend std::istream &operator>>(std::istream &is, ProtoVM &m);
    std::string model() const { return _model; }
    int core() const { return _core; }
    int ram() const { return _ram; }
    int node() const { return _node; }
};

#endif