#include "ProtoVM.h"
#include "Util.h"

std::ostream &operator<<(std::ostream &os, const ProtoVM &m)
{
    os << "[ProtoVM](" << std::endl;
    os << "\t" << m._model << std::endl;
    os << "\t" << m._core << std::endl;
    os << "\t" << m._ram << std::endl;
    os << "\t" << m._node << std::endl;
    os << ")" << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, ProtoVM &m)
{
    std::string line;
    std::getline(is, line);
    std::istringstream in = strin(line);
    in >> m._model >> m._core >> m._ram >> m._node;
    return is;
}
