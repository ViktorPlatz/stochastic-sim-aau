#include "SymbolTable.hpp"

namespace stochastic {
    template <typename Key, typename Value>
    void SymbolTable<Key, Value>::add(const Key& key, const Value& value) {
        if (contains(key)) {
            throw std::runtime_error("Key already exists in symbol table");
        }
        table[key] = value;
    }

    template <typename Key, typename Value>
    Value& SymbolTable<Key, Value>::get(const Key& key) {
        auto it = table.find(key);
        if (it == table.end()) {
            throw std::runtime_error("Key not found in symbol table");
        }
        return it->second;
    }

    template <typename Key, typename Value>
    const Value& SymbolTable<Key, Value>::get(const Key& key) const {
        auto it = table.find(key);
        if (it == table.end()) {
            throw std::runtime_error("Key not found in symbol table");
        }
        return it->second;
    }

    template <typename Key, typename Value>
    bool SymbolTable<Key, Value>::contains(const Key& key) const {
        return table.find(key) != table.end();
    }
}