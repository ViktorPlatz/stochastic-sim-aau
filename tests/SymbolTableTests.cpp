#include <doctest/doctest.h>
#include "StochasticLib.hpp"

using namespace stochastic;

// 9. Implement unit tests (e.g. test symbol table methods, their failure cases,
// pretty-printing reaction rules, etc).

TEST_CASE("SymbolTable: add and get") {
  SymbolTable<Species, int> table;
  Species a("A");

  table.add(a, 3);
  CHECK(table.get(a) == 3);
}

TEST_CASE("SymbolTable: duplicate add throws") {
  SymbolTable<Species, int> table;
  Species a("A");

  table.add(a, 2.0);
  CHECK_THROWS_AS(table.add(a, 4.0), std::runtime_error);
}

TEST_CASE("SymbolTable: get missing key throws") {
  SymbolTable<Species, int> table;
  Species a("A");

  CHECK_THROWS_AS(table.get(a), std::runtime_error);
}

TEST_CASE("SymbolTable: contains works") {
  SymbolTable<Species, int> table;
  Species a("A"), b("B");

  table.add(a, 1.0);
  CHECK(table.contains(a));
  CHECK_FALSE(table.contains(b));
}

TEST_CASE("SymbolTable: getAllKeys returns correct keys") {
  SymbolTable<Species, int> table;
  Species a("A"), b("B");

  table.add(a, 1.0);
  table.add(b, 2.0);

  auto keys = table.getAllKeys();
  CHECK(keys.size() == 2);
  CHECK((keys[0] == a ||
         keys[1] == a));  // Because we use unordered_map, order is not
                          // guaranteed - We just check both possibilities
  CHECK((keys[0] == b || keys[1] == b));
}

TEST_CASE("SymbolTable: getAll returns key-value pairs") {
  SymbolTable<Species, int> table;
  Species a("A"), b("B");

  table.add(a, 1.0);
  table.add(b, 2.0);

  auto all = table.getAll();
  CHECK(all.size() == 2);

  std::unordered_map<std::string, int> map;
  for (const auto& [s, v] : all) {
    map[s.getName()] = v;
  }

  CHECK(map["A"] == doctest::Approx(1.0));
  CHECK(map["B"] == doctest::Approx(2.0));
}