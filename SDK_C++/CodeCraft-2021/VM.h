#ifndef VM_H_
#define VM_H_


#include "ProtoVM.h"

class Server;
class VM
{
private:
    int vid;        //虚拟机id
    Server &server; //所在的服务器
    ProtoVM &pvm;   //虚拟机型号
    char node;      // A节点或B节点,双节点为'D'
public:
    VM(int vid, Server &server, ProtoVM &pvm, char node) : vid(vid), server(server), pvm(pvm), node(node) {}
};

#endif