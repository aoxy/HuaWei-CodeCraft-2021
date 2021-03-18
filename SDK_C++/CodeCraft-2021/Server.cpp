#include "Server.h"
#include "VM.h"
#include "Util.h"

//匹配度，就是要求核多的虚拟机该装在剩余核多的机器上，假设装完剩ncore,nram
//max(ncore/nram,nram/ncore)越小匹配度越好
double Server::match(ProtoVM pvm) const
{
    if (pvm.node() == 0)
    {
        int ncore = pvm.core();
        int nram = pvm.ram();
        if (ncore <= acore && nram <= aram && ncore <= bcore && nram <= bram)
        { //两个节点都能部署，部署在大节点上
            if (AgtB())
            {
                double rram = aram - nram + 0.1;
                double rcore = acore - ncore + 0.1;
                return MAX(rram / rcore, rcore / rram);
            }
            else
            {
                double rram = bram - nram + 0.1;
                double rcore = bcore - ncore + 0.1;
                return MAX(rram / rcore, rcore / rram);
            }
        }
        else if (ncore <= acore && nram <= aram)
        { //只能部署在A上
            double rram = aram - nram + 0.1;
            double rcore = acore - ncore + 0.1;
            return MAX(rram / rcore, rcore / rram);
        }
        else if (ncore <= bcore && nram <= bram)
        { //只能部署在B上
            double rram = bram - nram + 0.1;
            double rcore = bcore - ncore + 0.1;
            return MAX(rram / rcore, rcore / rram);
        }
        else
            return 1e10;
    }
    else
    {
        int halfcore = pvm.core() >> 1;
        int halfram = pvm.ram() >> 1;
        if (halfcore <= acore && halfram <= aram && halfcore <= bcore && halfram <= bram)
        {
            double arram = aram - halfram + 0.1;
            double arcore = acore - halfcore + 0.1;
            double amax = MAX(arram / arcore, arcore / arram);
            double brram = bram - halfram + 0.1;
            double brcore = bcore - halfcore + 0.1;
            double bmax = MAX(brram / brcore, brcore / brram);
            double abbalance = MAX((arram + arcore) / (brram + brcore), (brram + brcore) / (arram + arcore));
            return MAX(abbalance, MAX(amax, bmax));
        }
        else
            return 1e10;
    }
    return 1e10;
}

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