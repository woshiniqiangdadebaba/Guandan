#ifndef PLAYER_H
#define PLAYER_H

#include <ctime>
#include <cstdlib>
#include <cstring>
#include <QList>
#include "onecard.h"

class Player
{
private:
    int initial_cards[108];

public:
    Player();
    void shuffle_cards();
    void make_player(QList <OneCard> cardarray[],int);
    void sort_player(QList <OneCard> cardarray[]);
};

#endif // PLAYER_H
