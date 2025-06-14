#include <doctest/doctest.h>
#include <fstream>
#include <sstream>
#include <filesystem>
#include "Graph.hpp"
#include "ExampleSimulations.hpp"

using namespace stochastic;

TEST_CASE("Graph::generateDotGraph returns valid DOT format") {
    auto vessel = seihr(100);  // Use your SEIHR example
    std::string dot = Graph::generateDotGraph(vessel);

    CHECK(dot.find("digraph {") != std::string::npos);
    CHECK(dot.find("shape=\"box\"") != std::string::npos);
    CHECK(dot.find("shape=\"oval\"") != std::string::npos);
    CHECK(dot.find("->") != std::string::npos);
    CHECK(dot.back() == '\n');
}

TEST_CASE("Graph::saveDotGraphToFile creates file with DOT content") {
    auto vessel = seihr(100);
    const std::string testFile = "test_output/graph_test.dot";

    std::filesystem::remove(testFile);
    Graph::saveDotGraphToFile(vessel, testFile);

    CHECK(std::filesystem::exists(testFile));

    std::ifstream file(testFile);
    std::stringstream buffer;
    buffer << file.rdbuf();

    std::string content = buffer.str();
    CHECK(content.find("digraph {") != std::string::npos);
    CHECK(content.find("shape=\"box\"") != std::string::npos);

    file.close();
    std::filesystem::remove(testFile);
}