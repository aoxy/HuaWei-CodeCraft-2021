#include <sstream>
#include "ProtoServer.h"
#include "Util.h"

std::ostream &operator<<(std::ostream &os, const ProtoServer &s)
{
    os << "[ProtoServer](" << std::endl;
    os << "\t" << s._model << std::endl;
    os << "\t" << s._core << std::endl;
    os << "\t" << s._ram << std::endl;
    os << "\t" << s._price << std::endl;
    os << "\t" << s._cost << std::endl;
    os << ")" << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, ProtoServer &s)
{
    std::string line;
    std::getline(is, line);
    std::istringstream in = strin(line);
    in >> s._model >> s._core >> s._ram >> s._price >> s._cost;
    return is;
}