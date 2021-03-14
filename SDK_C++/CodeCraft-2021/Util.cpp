#include <string>
#include <sstream>
#include "Util.h"

int readInt(char *&t)
{
    int acc = 0;
    while (*t >= '0' && *t <= '9')
        acc = acc * 10 - '0' + *t++;
    while (*t && (*t < '0' || *t > '9'))
        t++;
    return acc;
}

std::istringstream strin(std::string input)
{
    for (auto i = input.begin(); i != input.end(); i++)
    {
        if (*i == '(' || *i == ',' || *i == ')')
            *i = ' ';
    }
    std::istringstream strin(input);
    return strin;
}