#ifndef VM_H_
#define VM_H_

#include "ProtoVM.h"

class VM
{
public:
    int vid;     //虚拟机id
    int sid;     //所在的服务器
    ProtoVM pvm; //虚拟机型号
    char node;   // A节点或B节点,双节点为'D'

    VM(int vid, int sid, ProtoVM pvm, char node) : vid(vid), sid(sid), pvm(pvm), node(node) {}
};

#endif