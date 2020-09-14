#include "onecard.h"

OneCard::OneCard()
{
    value=0;
    memset(num,0,sizeof(num));
    color=0;
}

void OneCard::make_card(int n, int special_card)
{
    if(n>103)
    {
        if(n%2)
        {
            value=17;
            num[0]='B';
            color=1;
        }
        else
        {
            value=16;
            num[0]='S';
            color=2;
        }
        return;
    }
    int value_card=n%13;
    value=value_card+1;
    if(value_card==0)value=14;
    if(value==special_card)value=15;
    switch(value_card)
    {
        case 0:strcpy(num," A");break;
        case 9:strcpy(num,"10");break;
        case 10:strcpy(num," J");break;
        case 11:strcpy(num," Q");break;
        case 12:strcpy(num," K");break;
        default:char j=value_card+49;num[0]=' ';num[1]=j;break;
    }
    int color_card=n/26;
    switch(color_card)
    {
        case 0:color=3;break;
        case 1:color=4;break;
        case 2:color=5;break;
        case 3:color=6;break;
    }
}
