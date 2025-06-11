#include "SpeciesCombination.hpp"
#include "Species.hpp"
#include <memory>
#include <vector>

namespace stochastic {

    SpeciesCombination operator+(const Species& lhs, const Species& rhs) {
        SpeciesCombination result;
        result.speciesList.push_back(lhs);
        result.speciesList.push_back(rhs);
        return result;
    }

    SpeciesCombination operator+(const SpeciesCombination& lhs, const Species& rhs) {
        SpeciesCombination result = lhs;
        result.speciesList.push_back(rhs);
        return result;
    }

    SpeciesCombination operator+(const Species& lhs, const SpeciesCombination& rhs) {
        SpeciesCombination result = rhs;
        result.speciesList.insert(result.speciesList.begin(), lhs);
        return result;
    }

    SpeciesCombination operator+(const SpeciesCombination& lhs, const SpeciesCombination& rhs) {
        SpeciesCombination result = lhs;
        result.speciesList.insert(result.speciesList.end(), rhs.speciesList.begin(), rhs.speciesList.end());
        return result;
    }

    std::ostream& operator<<(std::ostream& os, const SpeciesCombination& sc) {
        os << "SpeciesCombination: ";
        for (const auto& species : sc.speciesList) {
            os << species.getName() << " ";
        }
        return os;
    }

    SpeciesCombination::SpeciesCombination() = default;
    SpeciesCombination::~SpeciesCombination() = default;


}
