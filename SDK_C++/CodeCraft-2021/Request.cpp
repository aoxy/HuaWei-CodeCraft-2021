#include "Request.h"
#include "Util.h"

std::ostream &operator<<(std::ostream &os, const Request &r)
{
    os << "[Request](" << std::endl;
    os << "\t" << r._optype << std::endl;
    os << "\t" << r._model << std::endl;
    os << "\t" << r._vid << std::endl;
    os << ")" << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, Request &r)
{
    std::string line;
    std::getline(is, line);
    std::istringstream in = strin(line);
    in >> r._optype;
    if (r._optype == "add")
    {
        in >> r._model >> r._vid;
    }
    else
    {
        in >> r._vid;
    }
    return is;
}
