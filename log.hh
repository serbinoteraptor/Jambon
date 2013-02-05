#ifndef LOG_HPP
# define LOG_HPP

# include <iostream>
# include <cmath>

#  define LOG(x)                                                        \
  {                                                                     \
    std::string func_name{__PRETTY_FUNCTION__};                         \
    size_t size = (40 < func_name.length()) ? 0 : 40 - func_name.length(); \
    std::string complete(size, ' ');                                    \
    std::cout << complete << func_name << "::> " << x << std::endl;       \
  }                                                                     \


#endif
