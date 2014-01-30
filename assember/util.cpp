#include <string>
#include <iostream>

#include "util.h"

std::string trim(const std::string& s)
{
   std::string rval;
   rval = s;
   size_t p = rval.find_first_not_of(" \t");
   rval.erase(0, p);

   p = rval.find_last_not_of(" \t");
   if (std::string::npos != p)
      rval.erase(p+1);

   return rval;
}

std::string cmd(const std::string& s) {
    std::string rval;
    size_t p = s.find_first_of(" \t\n");
    rval = s.substr(0,p);
    return rval;
}

std::string argify(const std::string& s) {
    std::string rval = "";
    size_t p = s.find_first_of(" \t\n");
    if (p == std::string::npos)
        return rval;
    rval = s.substr(p);
    rval = trim(rval);
    //remove trailing space as well
    p = rval.find_first_of(" \t\n");
    rval = rval.substr(0,p);
    return rval;
}
