#ifndef SPECIES_HPP
#define SPECIES_HPP

#include <string>

namespace stochastic {

    class Species {
        std::string name;
    public:
        Species();
        Species(const std::string& name);
        const std::string& getName() const;
        std::ostream& print(std::ostream& os) const;
    };
}

#endif