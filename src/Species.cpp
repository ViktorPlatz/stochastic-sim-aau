#include "SpeciesCombination.hpp"
#include "Species.hpp"
#include <memory>
#include <iomanip>
namespace stochastic {
    Species::Species(const std::string& name){
        this->name = name;
    }

    const std::string& Species::getName() const {
        return name;
    }

    std::ostream& Species::print(std::ostream& os) const {
        os << "Species: " << name;
        return os;
    }

    bool Species::operator==(const Species& other) const {
        return name == other.name;
    }
}
