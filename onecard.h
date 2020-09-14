#ifndef ONECARD_H
#define ONECARD_H

#include <cstring>

class OneCard
{
public:
    int value;
    int color;
    char num[3];

public:
    OneCard();
    void make_card(int,int);
};

#endif // ONECARD_H
