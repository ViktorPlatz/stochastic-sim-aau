#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Vessel.hpp"

namespace stochastic {

    class Graph {
    public:
        static std::string generateDotGraph(const Vessel& vessel);
        static void printDotGraph(const Vessel& vessel);
        static void saveDotGraphToFile(const Vessel& vessel, const std::string& filename);
    };

}

#endif
