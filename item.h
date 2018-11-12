#ifndef ITEM_H
#define ITEM_H

#include <algorithm>
#include <string>
#include <fstream>


class Item
{
public:
    std::string getName() const;
    std::string getMeasure() const;
    void setName(std::string&);
    void setMeasure(std::string&);
    virtual int identify() const = 0;
protected:
    std::string name;
    std::string measure; //seconds, minutes, hours...
};

#endif // ITEM_H
