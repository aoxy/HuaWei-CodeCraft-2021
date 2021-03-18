#ifndef PROTO_SERVER_H_
#define PROTO_SERVER_H_

#define MAGIC_FACTOR 1.2

#include <iostream>
#include <string>
#include <unordered_map>

/**
 * 描述一种类型的服务器，数据格式为：(型号,CPU核数, 内存大小, 硬件成本, 每日能耗成本)。
 * 例如(NV603,92, 324, 53800, 500)表示一种服务器类型，其型号为NV603，包含 92个CPU核心，
 * 324G 内存，硬件成本为53800，每日能耗成本为 500。
 * CPU核数，内存大小，硬件成本，每日能耗成本均为正整数。
 * 每台服务器的CPU核数以及内存大小不超过1024，硬件成本不超过 5×105，每日能耗成本不超过5000。
 * 服务器型号长度不超过 20，仅由数字和大小写英文字符构成。
 */
class ProtoServer
{
private:
    std::string _model;
    int _core;
    int _ram;
    int _price;
    int _cost;

public:
    ProtoServer() {}
    ProtoServer(std::string model, int core, int ram, int price, int cost)
        : _model(model), _core(core), _ram(ram), _price(price), _cost(cost) {}
    friend std::ostream &operator<<(std::ostream &os, const ProtoServer &s);
    friend std::istream &operator>>(std::istream &is, ProtoServer &s);
    std::string model() const { return _model; }
    bool operator<(const ProtoServer &that) const
    {
        return (MAGIC_FACTOR * _core + _ram) < (MAGIC_FACTOR * that._core + that._ram);
    }
    bool greatthan(const ProtoServer &that) const
    {
        return (MAGIC_FACTOR * _core + _ram) > 0.7 * (MAGIC_FACTOR * that._core + that._ram);
    }
    int core() const { return _core; }
    int ram() const { return _ram; }
    int price() const { return _price; }
    int cost() const { return _cost; }
};

#endif