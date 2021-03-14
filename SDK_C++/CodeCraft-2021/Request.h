#ifndef REQUEST_H_
#define REQUEST_H_

#include <iostream>
#include <string>

/**
 * 描述一条请求数据。请求数据的格式为：(add, 虚拟机型号, 虚拟机ID)或(del,虚拟机ID)分别表示创建一台虚拟机或者删除一台虚拟机。
 * 例如(add,c3.large.4, 1)表示创建一台型号为 c3.large.4，ID为1的虚拟机；(del,1)表示删除ID为1的虚拟机。
 * 虚拟机的ID均为整数，每个创建请求的虚拟机ID唯一，范围不超过带符号32位整数表示的范围。
 * 对于删除操作，数据集保证对应ID的虚拟机一定存在。
 * 用户创建请求数量总数不超过105。
 */
class Request
{
private:
    std::string _optype;
    std::string _model;
    int _id;

public:
    Request() {}
    Request(std::string _optype, std::string _model, int _id)
        : _optype(_optype), _model(_model), _id(_id) {}
    friend std::ostream &operator<<(std::ostream &os, const Request &r);
    friend std::istream &operator>>(std::istream &is, Request &r);
    std::string optype(){return _optype; };
    std::string model(){return _model;}
    int id(){return _id; }
};

#endif