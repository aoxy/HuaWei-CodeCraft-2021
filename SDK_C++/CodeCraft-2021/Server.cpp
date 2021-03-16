#include "Server.h"
#include "VM.h"

int Server::deploy(ProtoVM pvm, int vid)
{
    if (pvm.node() == 0)
    {
        int ncore = pvm.core();
        int nram = pvm.ram();
        if (ncore <= acore && nram <= aram && ncore <= bcore && nram <= bram)
        { //两个节点都能部署，部署在大节点上
            if (AgtB())
            {
                acore -= ncore;
                aram -= nram;
                svms.insert({vid, VM(vid, this->sid, pvm, 'A')});
                return 0;
            }
            else
            {
                bcore -= ncore;
                bram -= nram;
                svms.insert({vid, VM(vid, this->sid, pvm, 'B')});
                return 1;
            }
        }
        else if (ncore <= acore && nram <= aram)
        { //只能部署在A上
            acore -= ncore;
            aram -= nram;
            svms.insert({vid, VM(vid, this->sid, pvm, 'A')});
            return 0;
        }
        else if (ncore <= bcore && nram <= bram)
        { //只能部署在B上
            bcore -= ncore;
            bram -= nram;
            svms.insert({vid, VM(vid, this->sid, pvm, 'B')});
            return 1;
        }
        else
            return -1;
    }
    else
    {
        int halfcore = pvm.core() >> 1;
        int halfram = pvm.ram() >> 1;
        if (halfcore <= acore && halfram <= aram && halfcore <= bcore && halfram <= bram)
        {
            acore -= halfcore;
            bcore -= halfcore;
            aram -= halfram;
            bram -= halfram;
            svms.insert({vid, VM(vid, this->sid, pvm, 'D')});
            return 2;
        }
        else
            return -1;
    }
    return -1;
}

void Server::del(VM vm)
{
    ProtoVM pvm = vm.pvm;
    svms.erase(vm.vid);
    if (vm.node == 'A')
    {
        acore += pvm.core();
        aram += pvm.ram();
    }
    else if (vm.node == 'B')
    {
        bcore += pvm.core();
        bram += pvm.ram();
    }
    else
    {
        acore += pvm.core() >> 1;
        aram += pvm.ram() >> 1;
        bcore += pvm.core() >> 1;
        bram += pvm.ram() >> 1;
    }
}