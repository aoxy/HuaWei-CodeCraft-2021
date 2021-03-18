#ifndef UTIL_H_
#define UTIL_H_

#define MAX(a, b) ((a) > (b)) ? (a) : (b)

#define MIN(a, b) ((a) < (b)) ? (a) : (b)

#include <sstream>
#include <string>

int readInt(char *&t);

std::istringstream strin(std::string input);

#endif