#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace Utils {
    std::vector<std::string> split(const std::string &s, char delim);
    std::string trim(const std::string &s);
}

#endif 