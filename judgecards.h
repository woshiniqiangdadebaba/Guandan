#ifndef JUDGECARDS_H
#define JUDGECARDS_H

#include <QList>
#include "onecard.h"

class JudgeCards
{
private:
    int special_card;

    void set_special_card(int);

    bool is_bomb(QList<OneCard> cards);

    int is_straight(QList<OneCard> cards);

    int is_straight_flush(QList<OneCard> cards);

    int is_sandaier(QList<OneCard> cards);

    int is_liandui(QList<OneCard> cards);

    int is_gangban(QList<OneCard> cards);

public:
    JudgeCards();
public:
    bool is_right_dis(QList<OneCard> card_before,QList<OneCard> card_now, int special_card);
};

#endif // JUDGECARDS_H
