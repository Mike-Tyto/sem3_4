#pragma once
#include "array.h"
#include "hasher.h"
#include "idict.h"
#include "list.h"
#include "stl_hasher.h"
#include <initializer_list>
#define DEFAULT_SIZE 8
#define MAX_LOAD_FACTOR 0.75
#define FACTOR 2

template <typename K, typename T>
class HashTable : public IDict<K, T> {
    protected:
    using bucket = LinkedList<Pair<K, T>>;
    using collision_list = DynamicArray<bucket>;
    using Iterator = typename LinkedList<Pair<K, T>>::Iterator;

    private:
    LinkedList<Pair<K, T>>* flatten = nullptr;
    collision_list hashTable;
    size_t count;
    IHasher<K>* hasher;

    public:
    HashTable()
        : hashTable(DEFAULT_SIZE)
        , hasher(new STLHasher<K>())
        , count(0) {
    }

    HashTable(IHasher<K>* hasher)
        : hashTable(DEFAULT_SIZE)
        , hasher(hasher)
        , count(0) {
    }

    HashTable(std::initializer_list<Pair<K, T>> args)
        : hashTable(args.size())
        , hasher(new STLHasher<K>())
        , count(0) {
        for (auto& e : args) {
            add(e.first, e.last);
        }
    }

    HashTable(IHasher<K>* hasher, std::initializer_list<Pair<K, T>> args)
        : hashTable(size_t(args.size()))
        , hasher(hasher)
        , count(0) {
        for (auto& e : args) {
            add(e.first, e.second);
        }
    }

    HashTable(const HashTable<K, T>& other)
        : hashTable(other.hashTable)
        , hasher(other.hasher->Copy())
        , count(other.count) {
    }

    HashTable(HashTable<K, T>&& other)
        : hashTable(std::move(other.hashTable))
        , hasher(other.hasher)
        , count(other.count) {
        other.count = 0;
        other.hasher = nullptr;
    }

    ~HashTable() {
        delete hasher;
        delete flatten;
    }

    Iterator begin() {
        delete flatten;
        flatten = new LinkedList<Pair<K, T>>();
        for (bucket& bucket : hashTable) {
            for (auto& e : bucket) {
                flatten->Append(e);
            }
        }
        return flatten->begin();
    }

    Iterator end() {
        if (flatten == nullptr) {
            throw std::logic_error("flatten is null");
        }
        return flatten->end();
    }

    bool contains_key(const K& key) const noexcept override {
        if (count == 0) {
            return false;
        }

        size_t index = hasher->hash(key) % get_capacity();
        auto& bucket = hashTable[index];
        for (auto& e : bucket) {
            if (e.first == key) {
                return true;
            }
        }
        return false;
    }

    void add(const K& key, const T& val) override {
        if (get_capacity() == 0) {
            hashTable.Resize(DEFAULT_SIZE);
        }
        if (contains_key(key)) {
            std::cout << "Key: " << key << std::endl;
            throw std::invalid_argument("Key already exists");
        }
        this->hashTable.Get(hash(key)).Append({ key, val });
        count++;
        reconstruct_if_needed();
    }

    void remove(const K& key) override {
        if (!contains_key(key)) {
            throw std::invalid_argument("Key does not exist");
        }
        auto& bucket = hashTable.Get(hash(key));
        for (int i = 0; i < bucket.GetLength(); i++) {
            if (bucket[i].first == key) {
                bucket.Remove(i);
                break;
            }
        }
        count--;
    }

    T get(const K& key) const override {
        auto& bucket = hashTable.Get(hash(key));
        for (auto& e : bucket) {
            if (e.first == key) {
                return e.last;
            }
        }
        throw std::invalid_argument("Key does not exist");
    }

    Pair<K, T*> get_entry(const K& key) override {
        auto& bucket = hashTable.Get(hash(key));
        for (auto& e : bucket) {
            if (e.first == key) {
                return Pair<K, T*>(e.first, &e.last);
            }
        }
        throw std::invalid_argument("Key does not exist");
    }

    size_t get_count() const noexcept override {
        return count;
    }

    size_t get_capacity() const noexcept override {
        return hashTable.GetSize();
    }

    private:
    void reconstruct_if_needed() noexcept {
        if (count >= MAX_LOAD_FACTOR * get_capacity()) {
            size_t new_capacity = get_capacity() * FACTOR;
            collision_list new_table = collision_list();
            new_table.Resize(new_capacity);

            for (auto& bucket : hashTable) {
                for (auto& e : bucket) {
                    size_t index = hasher->hash(e.first) % new_capacity;
                    new_table[index].Append(e);
                }
            }
            hashTable = std::move(new_table);
        }
    }

    size_t hash(const K& key) const noexcept {
        return hasher->hash(key) % get_capacity();
    }

    friend std::ostream& operator<<(std::ostream& os, HashTable<K, T>& hashTable) {
        size_t i = 0;
        for (auto x : hashTable.hashTable) {
            x.GetLength() == 0 ? os << i++ << "\t=> [----]\n" : os << i++ << "\t=>" << x << std::endl;
        }
        return os;
    }
};
