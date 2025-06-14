#include "SpeciesCombination.hpp"
#include "Species.hpp"
#include <memory>
#include <vector>
#include <iomanip>

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
        const auto& speciesList = sc.getSpeciesList();
        for (size_t i = 0; i < speciesList.size(); ++i) {
            os << speciesList[i].getName();
            if (i != speciesList.size() - 1) {
                os << " + ";
            }
        }
        return os;
    }

    bool SpeciesCombination::operator==(const SpeciesCombination& other) const {
        if (speciesList.size() != other.speciesList.size()) {
            return false;
        }
        for (size_t i = 0; i < speciesList.size(); ++i) {
            if (!(speciesList[i] == other.speciesList[i])) {
                return false;
            }
        }
        return true;
    }

    SpeciesCombination::SpeciesCombination() = default;

    SpeciesCombination::SpeciesCombination(const Species& species) {
        speciesList.push_back(species);
    }

    const std::vector<Species>& SpeciesCombination::getSpeciesList() const {
        return speciesList;
    }

}
