#include "item.h"


std::string Item::getName() const
{
    return name;
}

std::string Item::getMeasure() const
{
    return measure;
}

void Item::setName(std::string &n)
{
    name = n;
}

void Item::setMeasure(std::string &m)
{
    measure = m;
}
