#include <doctest/doctest.h>

#include <filesystem>
#include <fstream>
#include <sstream>

#include "StochasticLib.hpp"

using namespace stochastic;
//9. Implement unit tests (e.g. test symbol table methods, their failure cases, pretty-printing reaction rules, etc).
TEST_CASE("Graph::generateDotGraph returns valid DOT format") {
  auto vessel = Seihr(100);
  std::string dot = Graph::generateDotGraph(vessel);

  CHECK(dot.find("digraph {") != std::string::npos);
  CHECK(dot.find("shape=\"box\"") != std::string::npos);
  CHECK(dot.find("shape=\"oval\"") != std::string::npos);
  CHECK(dot.find("->") != std::string::npos);
  CHECK(dot.back() == '\n');
}

TEST_CASE("Graph::saveDotGraphToFile creates file with DOT content") {
  auto vessel = Seihr(100);
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