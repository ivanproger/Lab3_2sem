#pragma once
#include <ostream>

template <typename Key, typename Value>
class IDictionary {
public:
    virtual void insert(const Key& key, const Value& value) = 0;
    virtual bool find(const Key& key, Value& value) const = 0;
    virtual void display(std::ostream& os) const = 0;
    virtual ~IDictionary() {}
};
