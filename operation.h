#ifndef OPERATION_H
#define OPERATION_H

#include "item.h"


class Operation : public Item
{
public:
    Operation();
    Operation(std::string, int, std::string);
    Operation(const Operation&);
    Operation(Operation&&);
    Operation& operator =(const Operation&);

    int getDuration() const;
    void setDuration(int);

    int identify() const override;
private:
    int duration;
};

#endif // OPERATION_H
