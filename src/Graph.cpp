#include "Graph.hpp"

#include <filesystem>

#include "Utils.hpp"
#include <sstream>
#include <iomanip>
#include <unordered_map>
#include <fstream>
#include <iostream>

namespace stochastic {

    std::string Graph::generateDotGraph(const Vessel& vessel) {
        std::ostringstream oss;
        const auto& speciesList = vessel.getSpecies();
        const auto& reactions = vessel.getReactions();

        oss << "digraph {\n";

        std::unordered_map<std::string, std::string> speciesToId;
        int sCounter = 0;
        for (const auto& s : speciesList) {
            if (isEnvironment(s)) continue;

            std::string id = "s" + std::to_string(sCounter++);
            speciesToId[s.getName()] = id;
            oss << id << "[label=\"" << s.getName()
                << "\",shape=\"box\",style=\"filled\",fillcolor=\"cyan\"];\n";
        }

        int rCounter = 0;
        for (const auto& r : reactions) {
            std::string rId = "r" + std::to_string(rCounter++);
            oss << rId << "[label=\"" << r.getRateConstant()
                << "\",shape=\"oval\",style=\"filled\",fillcolor=\"yellow\"];\n";

            for (const auto& s : r.getInput()) {
                std::string sid = speciesToId.at(s.getName());
                oss << sid << " -> " << rId << ";\n";
            }

            for (const auto& s : r.getOutput()) {
                if (isEnvironment(s)) continue;
                std::string sid = speciesToId.at(s.getName());
                oss << rId << " -> " << sid << ";\n";
            }
        }

        oss << "}\n";
        return oss.str();
    }

    void Graph::printDotGraph(const Vessel& vessel) {
        std::cout << generateDotGraph(vessel);
    }

    void Graph::saveDotGraphToFile(const Vessel& vessel, const std::string& filename) {
        std::filesystem::path path(filename);
        std::filesystem::create_directories(path.parent_path());

        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Could not open file: " + filename);
        }
        outFile << generateDotGraph(vessel);
        outFile.close();
    }

}
