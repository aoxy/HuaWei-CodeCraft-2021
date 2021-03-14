#ifndef SERVER_H_
#define SERVER_H_

#include <iostream>
#include <string>

/**
 * 描述一种类型的服务器，数据格式为：(型号,CPU核数, 内存大小, 硬件成本, 每日能耗成本)。
 * 例如(NV603,92, 324, 53800, 500)表示一种服务器类型，其型号为NV603，包含 92个CPU核心，
 * 324G 内存，硬件成本为53800，每日能耗成本为 500。
 * CPU核数，内存大小，硬件成本，每日能耗成本均为正整数。
 * 每台服务器的CPU核数以及内存大小不超过1024，硬件成本不超过 5×105，每日能耗成本不超过5000。
 * 服务器型号长度不超过 20，仅由数字和大小写英文字符构成。
 */
class Server
{
private:
    std::string model;
    int core;
    int ram;
    int price;
    int cost;

public:
    Server() {}
    Server(std::string model, int core, int ram, int price, int cost)
        : model(model), core(core), ram(ram), price(price), cost(cost) {}
    friend std::ostream &operator<<(std::ostream &os, const Server &s);
    friend std::istream &operator>>(std::istream &is, Server &s);
};

#endif