#include <sstream>
#include "Server.h"
#include "util.h"

std::ostream &operator<<(std::ostream &os, const Server &s)
{
    os << "(" << std::endl;
    os << "\t" << s.model << std::endl;
    os << "\t" << s.core << std::endl;
    os << "\t" << s.ram << std::endl;
    os << "\t" << s.price << std::endl;
    os << "\t" << s.cost << std::endl;
    os << ")" << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, Server &s)
{
    std::string line;
    std::getline(is, line);
    std::istringstream in = strin(line);
    in >> s.model >> s.core >> s.ram >> s.price >> s.cost;
    return is;
}