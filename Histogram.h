#pragma once
#include <ostream>

class Histogram {
public:
    virtual void display(std::ostream& os) const = 0;
    virtual ~Histogram() {}
};
