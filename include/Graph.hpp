#ifndef GRAPH_HPP
#define GRAPH_HPP

#include "Vessel.hpp"

namespace stochastic {

    class Graph {
    public:
        //2. Provide pretty-printing of the reaction network in a) human readable format and b) network graph (e.g. Fig. 4).
        static std::string generateDotGraph(const Vessel& vessel);
        static void printDotGraph(const Vessel& vessel);
        static void saveDotGraphToFile(const Vessel& vessel, const std::string& filename);
    };

}

#endif
