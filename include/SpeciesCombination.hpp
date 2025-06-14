
#ifndef SPECIESCOMBINATION_HPP
#define SPECIESCOMBINATION_HPP
#include "Species.hpp"
#include <vector>

namespace stochastic {

    class SpeciesCombination {
    private:
		std::vector<Species> speciesList;

        friend SpeciesCombination operator+(const Species& lhs, const Species& rhs);
        friend SpeciesCombination operator+(const SpeciesCombination& lhs, const Species& rhs);
        friend SpeciesCombination operator+(const Species& lhs, const SpeciesCombination& rhs);
        friend SpeciesCombination operator+(const SpeciesCombination& lhs, const SpeciesCombination& rhs);

        friend std::ostream& operator<<(std::ostream& os, const SpeciesCombination& sc);
    public:
        SpeciesCombination();
        SpeciesCombination(const Species& species);
        bool operator==(const SpeciesCombination& other) const;
        const std::vector<Species>& getSpeciesList() const;
    };

    SpeciesCombination operator+(const Species& lhs, const Species& rhs);
    SpeciesCombination operator+(const SpeciesCombination& lhs, const Species& rhs);
    SpeciesCombination operator+(const Species& lhs, const SpeciesCombination& rhs);
    SpeciesCombination operator+(const SpeciesCombination& lhs, const SpeciesCombination& rhs);

    std::ostream& operator<<(std::ostream& os, const SpeciesCombination& sc);
}

#endif
