#pragma once
#include "IDictionary.h"
#include "Pair.h"
#include "DynamicArray.h"
#include <functional>
#include <ostream>

template <typename Key, typename Value>
class HashTable : public IDictionary<Key, Value> {
private:
    DynamicArray<Pair<Key, Value>>* buckets;
    int bucketCount;

    int hashFunction(const Key& key) const {
        std::hash<Key> h;
        return (int)(h(key) % bucketCount);
    }

public:
    HashTable(int size) : bucketCount(size) {
        buckets = new DynamicArray<Pair<Key, Value>>(size);
        for (int i = 0; i < size; i++) {
            buckets->Set(i, Pair<Key, Value>());
        }
    }

    ~HashTable() {
        delete buckets;
    }

    void insert(const Key& key, const Value& value) override {
        int index = hashFunction(key);
        for (int i = 0; i < bucketCount; ++i) {
            int idx = (index + i) % bucketCount;
            Pair<Key, Value> p = buckets->GetElem(idx);
            if (p.key == Key() && p.value == Value()) {
                buckets->Set(idx, Pair<Key, Value>(key, value));
                return;
            }
            else if (p.key == key) {
                p.value = p.value + value;
                buckets->Set(idx, p);
                return;
            }
        }
    }

    bool find(const Key& key, Value& value) const override {
        int index = hashFunction(key);
        for (int i = 0; i < bucketCount; ++i) {
            int idx = (index + i) % bucketCount;
            Pair<Key, Value> p = buckets->GetElem(idx);
            if (p.key == key) {
                value = p.value;
                return true;
            }
            if (p.key == Key() && p.value == Value()) {
                return false;
            }
        }
        return false;
    }

    // Удаляем std::cout из display
    void display(std::ostream& os) const override {
        // Пусто, переносим вывод в display.h
    }

    void getAllPairs(DynamicArray<Pair<Key, Value>>& arr) const {
        for (int i = 0; i < bucketCount; i++) {
            Pair<Key, Value> p = buckets->GetElem(i);
            if (!(p.key == Key() && p.value == Value())) {
                arr.Append(p);
            }
        }
    }
};
