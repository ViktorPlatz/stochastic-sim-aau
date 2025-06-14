#ifndef SPECIES_HPP
#define SPECIES_HPP

#include <string>
#include <functional>

namespace stochastic {

    class Species {
        std::string name;
    public:
        Species();
        Species(const std::string& name);
        const std::string& getName() const;
        std::ostream& print(std::ostream& os) const;
        bool operator==(const Species& other) const;

    };
}


namespace std {
    template <>
    struct hash<stochastic::Species> {
        std::size_t operator()(const stochastic::Species& s) const noexcept {
            return std::hash<std::string>{}(s.getName());
        }
    };
}

#endif