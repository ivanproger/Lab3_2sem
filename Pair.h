#pragma once

template <typename Key, typename Value>
class Pair {
public:
    Key key;
    Value value;

    Pair() : key(Key()), value(Value()) {}
    Pair(const Key& k, const Value& v) : key(k), value(v) {}
};
