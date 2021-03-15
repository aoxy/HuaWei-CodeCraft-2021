#include "Server.h"
#include "VM.h"

int Server::add(ProtoVM &pvm, int vid)
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
                vms.insert({vid, VM(vid, *this, pvm, 'A')});
                return 0;
            }
            else
            {
                bcore -= ncore;
                bram -= nram;
                vms.insert({vid, VM(vid, *this, pvm, 'B')});
                return 1;
            }
        }
        else if (ncore <= acore && nram <= aram)
        { //只能部署在A上
            acore -= ncore;
            aram -= nram;
            vms.insert({vid, VM(vid, *this, pvm, 'A')});
            return 0;
        }
        else if (ncore <= bcore && nram <= bram)
        { //只能部署在B上
            acore -= ncore;
            aram -= nram;
            vms.insert({vid, VM(vid, *this, pvm, 'B')});
            return 0;
        }
        else
            return -1;
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
            vms.insert({vid, VM(vid, *this, pvm, 'D')});
            return 2;
        }
        else
            return -1;
    }
    return -1;
}