#include "player.h"

Player::Player()
{

}

void Player::shuffle_cards()
{
    for(int i=0;i<108;i++)initial_cards[i]=i;
    srand(time(0));
    for(int i=0;i<200;i++)
    {
        int rand_num1=rand()%108;
        int rand_num2=rand()%108;
        int temp=initial_cards[rand_num1];
        initial_cards[rand_num1]=initial_cards[rand_num2];
        initial_cards[rand_num2]=temp;
    }
}

void Player::make_player(QList<OneCard> cardarray[], int special_card)
{
    for(int i=0;i<4;i++)
    {
        for(int j=27*i;j<27*(i+1);j++)
        {
            OneCard m;
            m.make_card(initial_cards[j],special_card);
            cardarray[i].append(m);
        }
    }
}

void Player::sort_player(QList <OneCard> cardarray[])
{
    for(int k=0;k<4;k++)
    {
        for(int i=0;i<27;i++)
        {
            for(int j=i+1;j<27;j++)
            {
                if(cardarray[k][i].value<cardarray[k][j].value||(cardarray[k][i].value==cardarray[k][j].value&&cardarray[k][i].color>cardarray[k][j].color))
                {
                    OneCard temp=cardarray[k][i];
                    cardarray[k][i]=cardarray[k][j];
                    cardarray[k][j]=temp;
                }
            }
        }
    }
}
