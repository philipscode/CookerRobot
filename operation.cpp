#include "operation.h"

Operation::Operation()
{
    name = "";
    duration = 0;
}

Operation::Operation(std::string n, int d, std::string m)
{
    name = n;
    duration = d;
    measure = m;
}

Operation::Operation(const Operation &other)
{
    name = other.getName();
    duration = other.getDuration();
    measure = other.getMeasure();
}

Operation::Operation(Operation &&other)
{
    name = other.getName();
    duration = other.getDuration();
    measure = other.getMeasure();
}

Operation& Operation::operator =(const Operation &other)
{
    name = other.getName();
    duration = other.getDuration();
    measure = other.getMeasure();
    return *this;
}

int Operation::getDuration() const
{
    return duration;
}

void Operation::setDuration(int d)
{
    if (d < 0)
    {
        duration = 0;
    }
    else
    {
        duration = d;
    }
}

int Operation::identify() const
{
    return 2;
}
