#include "Criteria.h"

int numericCriterion(const int& value) {
    return value;
}

int heightCriterion(const Person& person) {
    return (int)person.getHeight();
}

