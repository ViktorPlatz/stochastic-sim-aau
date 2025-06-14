#ifndef UTILS_HPP
#define UTILS_HPP
#include "Species.hpp"

namespace stochastic {
    inline bool isEnvironment(const Species& s) {
        return s.getName() == "env";
    }
}



#endif
