#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP


#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
/*3. Implement a generic symbol table to store and lookup objects of user-defined key and value types. Support
failure cases when a) the table does not contain a looked up symbol, b) the table already contains a symbol that
is being added. Demonstrate the usage of the symbol table with the reactants (names and initial counts).*/
namespace stochastic {

    template <typename Key, typename Value>
    class SymbolTable {
    public:
        Value& add(const Key& key, const Value& value) {
                if (contains(key)) {
                    throw std::runtime_error("Key already exists in symbol table");
                }
                table[key] = value;
                return table[key];
        }

        Value& get(const Key& key) {
            auto it = table.find(key);
            if (it == table.end()) {
                throw std::runtime_error("Key not found in symbol table");
            }
            return it->second;
        }

        const Value& get(const Key& key) const {
            auto it = table.find(key);
            if (it == table.end()) {
                throw std::runtime_error("Key not found in symbol table");
            }
            return it->second;
        }

        bool contains(const Key& key) const {
            return table.find(key) != table.end();
        }

        std::vector<Key> getAllKeys() const {
            std::vector<Key> keys;
            keys.reserve(table.size());
            for (const auto& pair : table) {
                keys.push_back(pair.first);
            }
            return keys;
        }


        std::vector<std::pair<Key, Value>> getAll() const {
            std::vector<std::pair<Key, Value>> items;
            items.reserve(table.size());
            for (const auto& pair : table) {
                items.emplace_back(pair.first, pair.second);
            }
            return items;
        }

    private:
        std::unordered_map<Key, Value> table;
    };

}

#endif
