#include "ingridient.h"


Ingridient::Ingridient()
{
    name = "";
    measure = "";
    amount = 0;
}

Ingridient::Ingridient(std::string n, std::string m, double a)
{
    name = n;
    measure = m;
    amount = a;
    std::transform(name.begin(), name.end(), name.begin(),
                   [](unsigned char c) -> unsigned char { return std::tolower(c); });
    std::transform(measure.begin(), measure.end(), measure.begin(),
                   [](unsigned char c) -> unsigned char { return std::tolower(c); });
    if (amount < 0) amount = 0;
}

Ingridient::Ingridient(const Ingridient &other)
{
    name = other.getName();
    measure = other.getMeasure();
    amount = other.getAmount();
}

Ingridient::Ingridient(Ingridient &&other)
{
    name = other.getName();
    measure = other.getMeasure();
    amount = other.getAmount();
}

Ingridient& Ingridient::operator =(const Ingridient &other)
{
    name = other.getName();
    measure = other.getMeasure();
    amount = other.getAmount();
    return *this;
}

double Ingridient::getAmount() const
{
    return amount;
}

void Ingridient::setAmount(double a)
{
    amount = a;
}

int Ingridient::identify() const
{
    return 1;
}
