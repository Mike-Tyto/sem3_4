#pragma once

#include <cstddef>

template<typename T>
class IHasher{
public:
    virtual size_t hash(const T& val) const noexcept = 0;
    virtual IHasher<T>* copy() const noexcept = 0;
};
