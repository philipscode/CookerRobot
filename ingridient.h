#ifndef INGRIDIENT_H
#define INGRIDIENT_H

#include "item.h"


class Ingridient : public Item
{
public:
    Ingridient(); //default constructor
    Ingridient(std::string, std::string, double); //initialization costructor
    Ingridient(const Ingridient&); //copy constructor
    Ingridient(Ingridient&&); //move constructor
    Ingridient& operator =(const Ingridient&); //copy assignment

    //getter methods
    double getAmount() const;

    //setter methods
    void setAmount(double);

    int identify() const override;
private:
    double amount;
};

#endif // INGRIDIENT_H
