#include "Utils.h"
#include <sstream>
#include <algorithm>
#include <cctype>

namespace Utils {
    std::vector<std::string> split(const std::string &s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss(s);
        std::string item;
        while (std::getline(ss, item, delim)) result.push_back(item);
        return result;
    }

    std::string trim(const std::string &s) {
        auto start = s.begin();
        while (start != s.end() && std::isspace((unsigned char)*start)) ++start;
        auto end = s.end();
        do { --end; } while (std::distance(start, end) >= 0 && std::isspace((unsigned char)*end));
        return std::string(start, end + 1);
    }
}