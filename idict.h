#pragma once
#include <stddef.h>
#include "pair.h"

template<typename K, typename T>
class IDict{
public:
    virtual size_t get_count() const noexcept = 0;
    virtual size_t get_capacity() const noexcept = 0;
    virtual T get(const K& key) const = 0;
    virtual Pair<K, T*> get_entry(const K& key) = 0;
    virtual bool contains_key(const K& key) const noexcept = 0;
    virtual void remove(const K& key) = 0;
    virtual void add(const K& key, const T& val) = 0;
    virtual ~IDict() = default;
};
