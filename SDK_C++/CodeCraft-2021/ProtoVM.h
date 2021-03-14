#ifndef PROTO_VM_H_
#define PROTO_VM_H_

#include <iostream>
#include <string>

/**
 * 描述一种类型的虚拟机，数据格式为：(型号,CPU核数, 内存大小, 是否双节点部署)。
 * 是否双节点部署用0和1表示，0 表示单节点部署，1 表示双节点部署。
 * 例如(s3.small.1,1, 1, 0)表示一种虚拟机类型，其型号为s3.small.1，所需 CPU核数为1，所需内存为 1G，单节点部署；
 * (c3.8xlarge.2, 32,64, 1)表示一种虚拟机类型，其型号为 c3.8xlarge.2，所需 CPU核数为32，所需内存为64G，双节点部署。
 * CPU核数，内存大小均为正整数。对于每种类型的虚拟机，数据集保证至少存在一种服务器可以容纳。
 * 虚拟机型号长度不超过20，仅由数字，大小写英文字符和'.'构成。
 */
class ProtoVM
{
private:
    std::string model;
    int core;
    int ram;
    int node;

public:
    ProtoVM() {}
    ProtoVM(std::string model, int core, int ram, int node)
        : model(model), core(core), ram(ram), node(node) {}
    friend std::ostream &operator<<(std::ostream &os, const ProtoVM &m);
    friend std::istream &operator>>(std::istream &is, ProtoVM &m);
};

#endif