#include "Request.h"
#include "Util.h"

std::ostream &operator<<(std::ostream &os, const Request &r)
{
    os << "(" << std::endl;
    os << "\t" << r.optype << std::endl;
    os << "\t" << r.model << std::endl;
    os << "\t" << r.id << std::endl;
    os << ")" << std::endl;
    return os;
}

std::istream &operator>>(std::istream &is, Request &r)
{
    std::string line;
    std::getline(is, line);
    std::istringstream in = strin(line);
    in >> r.optype;
    if (r.optype == "add")
    {
        in >> r.model >> r.id;
    }
    else
    {
        in >> r.id;
    }
    return is;
}
