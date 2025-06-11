#ifndef SYMBOLTABLE_HPP
#define SYMBOLTABLE_HPP

#include <unordered_map>
#include <string>
#include <stdexcept>

namespace stochastic {

    template <typename Key, typename Value>
    class SymbolTable {
    public:
        void add(const Key& key, const Value& value);
        Value& get(const Key& key);
        const Value& get(const Key& key) const;
        bool contains(const Key& key) const;
    private:
        std::unordered_map<Key, Value> table;
    };

}

#endif
