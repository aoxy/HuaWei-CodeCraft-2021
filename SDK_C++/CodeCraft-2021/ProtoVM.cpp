#include "ProtoVM.h"
#include "Util.h"

std::ostream &operator<<(std::ostream &os, const ProtoVM &m)
{
    os << "(" << std::endl;
    os << "\t" << m.model << std::endl;
    os << "\t" << m.core << std::endl;
    os << "\t" << m.ram << std::endl;
    os << "\t" << m.node << std::endl;
    os << ")" << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, ProtoVM &m)
{
    std::string line;
    std::getline(is, line);
    std::istringstream in = strin(line);
    in >> m.model >> m.core >> m.ram >> m.node;
    return is;
}
