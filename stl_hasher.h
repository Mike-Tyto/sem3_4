 #pragma once

#include "hasher.h"
#include <functional>

template <typename K>
class STLHasher : public IHasher<K>
{
public:
    size_t hash(const K& key) const noexcept override
    {
        return std::hash<K> {}(key);
    }

    IHasher<K>* copy() const noexcept override
    {
        return new STLHasher<K>();
    } 
};