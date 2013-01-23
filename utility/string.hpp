#ifndef UTILITY_STRINGS_HPP
# define UTILITY_STRINGS_HPP

#include <string>
#include <vector>
#include <sstream>

namespace utility
{
  namespace string
  {
    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems) {
      std::stringstream ss(s);
      std::string item;
      while(std::getline(ss, item, delim))
      {
        elems.push_back(item);
      }
      return elems;
    }

    std::vector<std::string> split(const std::string &s, char delim) {
      std::vector<std::string> elems;
      return split(s, delim, elems);
    }
  }
}
#endif
