#include "judgecards.h"

JudgeCards::JudgeCards()
{

}

void JudgeCards::set_special_card(int n)
{
    special_card=n;
}

//判断是否为炸弹
bool JudgeCards::is_bomb(QList<OneCard> cards)
{
    if(cards.length()<4)return false;

    if(cards.length()==4)
    {
        if(cards[0].value==17&&cards[1].value==17&&cards[2].value==16&&cards[3].value==16)return true;

        if(cards[0].value==cards[1].value&&cards[0].value==cards[2].value&&cards[0].value==cards[3].value)
        {
            return true;
        }
        if(cards[0].value==15&&cards[0].color==3&&cards[1].value==cards[2].value&&cards[1].value==cards[3].value)
        {
            cards[0].value=cards[1].value;
            return true;
        }
        if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color==3&&cards[2].value==cards[3].value)
        {
                cards[0].value=cards[2].value;
                cards[1].value=cards[2].value;
                return true;
        }
        return false;
    }

    if(cards.length()==5)
    {
        if(cards[0].value==cards[1].value&&cards[0].value==cards[2].value&&cards[0].value==cards[3].value&&cards[0].value==cards[4].value)
        {
            return true;
        }
        if(cards[0].value==15&&cards[0].color==3&&cards[1].value==cards[2].value&&cards[1].value==cards[3].value&&cards[1].value==cards[4].value)
        {
            cards[0].value=cards[1].value;
            return true;
        }
        if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color==3&&cards[2].value==cards[3].value&&cards[2].value==cards[4].value)
        {
                cards[0].value=cards[2].value;
                cards[1].value=cards[2].value;
                return true;
        }
        return false;
    }

    if(cards.length()==6)
    {
        if(cards[0].value==cards[1].value&&cards[0].value==cards[2].value&&cards[0].value==cards[3].value&&cards[0].value==cards[4].value&&cards[0].value==cards[5].value)
        {
            return true;
        }
        if(cards[0].value==15&&cards[0].color==3&&cards[1].value==cards[2].value&&cards[1].value==cards[3].value&&cards[1].value==cards[4].value&&cards[1].value==cards[5].value)
        {
            cards[0].value=cards[1].value;
            return true;
        }
        if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color==3&&cards[2].value==cards[3].value&&cards[2].value==cards[4].value&&cards[2].value==cards[5].value)
        {
                cards[0].value=cards[2].value;
                cards[1].value=cards[2].value;
                return true;
        }
        return false;
    }

    if(cards.length()==7)
    {
        if(cards[0].value==cards[1].value&&cards[0].value==cards[2].value&&cards[0].value==cards[3].value&&cards[0].value==cards[4].value&&cards[0].value==cards[5].value&&cards[0].value==cards[6].value)
        {
            return true;
        }
        if(cards[0].value==15&&cards[0].color==3&&cards[1].value==cards[2].value&&cards[1].value==cards[3].value&&cards[1].value==cards[4].value&&cards[1].value==cards[5].value&&cards[1].value==cards[6].value)
        {
            cards[0].value=cards[1].value;
            return true;
        }
        if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color==3&&cards[2].value==cards[3].value&&cards[2].value==cards[4].value&&cards[2].value==cards[5].value&&cards[2].value==cards[6].value)
        {
                cards[0].value=cards[2].value;
                cards[1].value=cards[2].value;
                return true;
        }
        return false;
    }

    if(cards.length()==8)
    {
        if(cards[0].value==cards[1].value&&cards[0].value==cards[2].value&&cards[0].value==cards[3].value&&cards[0].value==cards[4].value&&cards[0].value==cards[5].value&&cards[0].value==cards[6].value&&cards[0].value==cards[7].value)
        {
            return true;
        }
        if(cards[0].value==15&&cards[0].color==3&&cards[1].value==cards[2].value&&cards[1].value==cards[3].value&&cards[1].value==cards[4].value&&cards[1].value==cards[5].value&&cards[1].value==cards[6].value&&cards[1].value==cards[7].value)
        {
            cards[0].value=cards[1].value;
            return true;
        }
        if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color==3&&cards[2].value==cards[3].value&&cards[2].value==cards[4].value&&cards[2].value==cards[5].value&&cards[2].value==cards[6].value&&cards[2].value==cards[7].value)
        {
                cards[0].value=cards[2].value;
                cards[1].value=cards[2].value;
                return true;
        }
        return false;
    }

    return false;
}

//判断是否为顺子,返回值为顺子中最大的牌
int JudgeCards::is_straight(QList<OneCard> cards)
{
    if(cards.length()!=5)return 0;

    if(cards[0].value!=15)
    {
        if(cards[0].value>15)return 0;

        if(cards[0].value==cards[1].value+1&&cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
        {
            return cards[0].value;
        }

        if(cards[0].value==14)
        {
            cards[0].value=1;\

            for(int i=0;i<5;i++)
            {
                for(int j=i+1;j<5;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[0].value==cards[1].value+1&&cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
            {
                return cards[0].value;
            }
        }
        return 0;
    }

    if(cards[0].value==15&&cards[0].color!=3)
    {
        for(int i=0;i<5;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=0;i<5;i++)
        {
            for(int j=i+1;j<5;j++)
            {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[0].value==cards[1].value+1&&cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
        {
            return cards[0].value;
        }

        if(cards[0].value==14)
        {
            cards[0].value=1;\

            for(int i=0;i<5;i++)
            {
                for(int j=i+1;j<5;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[0].value==cards[1].value+1&&cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
            {
                return cards[0].value;
            }
        }
        return 0;
    }

    if(cards[0].value==15&&cards[0].color==3&&cards[1].value!=15)
    {
        if(cards[1].value==cards[2].value+1)
        {
            if(cards[2].value==cards[3].value+1)
            {
                if(cards[3].value==cards[4].value+1)
                {
                    if(cards[1].value==14)return cards[1].value;
                    else return cards[1].value+1;
                }
                else if(cards[3].value==cards[4].value+2)
                {
                    return cards[1].value;
                }
            }
            else if(cards[2].value==cards[3].value+2&&cards[3].value==cards[4].value+1)
            {
                return cards[1].value;
            }
        }
        else if(cards[1].value==cards[2].value+2&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
        {
            return cards[1].value;
        }

        if(cards[1].value==14)
        {
            cards[1].value=1;

            for(int i=1;i<5;i++)
            {
                for(int j=i+1;j<5;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[1].value==cards[2].value+1)
            {
                if(cards[2].value==cards[3].value+1)
                {
                    if(cards[3].value==cards[4].value+1)
                    {
                        return cards[1].value+1;
                    }
                    else if(cards[3].value==cards[4].value+2)
                    {
                        return cards[1].value;
                    }
                }
                else if(cards[2].value==cards[3].value+2&&cards[3].value==cards[4].value+1)
                {
                    return cards[1].value;
                }
            }
            else if(cards[1].value==cards[2].value+2&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
            {
                return cards[1].value;
            }
        }
        return 0;
    }

    if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color!=3)
    {
        for(int i=1;i<5;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=1;i<5;i++)
        {
            for(int j=i+1;j<5;j++)
            {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[1].value==cards[2].value+1)
        {
            if(cards[2].value==cards[3].value+1)
            {
                if(cards[3].value==cards[4].value+1)
                {
                    if(cards[1].value==14)return cards[1].value;
                    else return cards[1].value+1;
                }
                else if(cards[3].value==cards[4].value+2)
                {
                    return cards[1].value;
                }
            }
            else if(cards[2].value==cards[3].value+2&&cards[3].value==cards[4].value+1)
            {
                return cards[1].value;
            }
        }
        else if(cards[1].value==cards[2].value+2&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
        {
            return cards[1].value;
        }

        if(cards[1].value==14)
        {
            cards[1].value=1;

            for(int i=1;i<5;i++)
            {
                for(int j=i+1;j<5;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[1].value==cards[2].value+1)
            {
                if(cards[2].value==cards[3].value+1)
                {
                    if(cards[3].value==cards[4].value+1)
                    {
                        return cards[1].value+1;
                    }
                    else if(cards[3].value==cards[4].value+2)
                    {
                        return cards[1].value;
                    }
                }
                else if(cards[2].value==cards[3].value+2&&cards[3].value==cards[4].value+1)
                {
                    return cards[1].value;
                }
            }
            else if(cards[1].value==cards[2].value+2&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
            {
                return cards[1].value;
            }
        }
        return 0;
    }

    if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color==3)
    {
        for(int i=2;i<5;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=2;i<5;i++)
        {
            for(int j=i+1;j<5;j++)
            {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[2].value==cards[3].value+1)
        {
            if(cards[3].value==cards[4].value+1)
            {
                if(cards[2].value>12)return 14;
                else return cards[2].value+2;
            }
            else if(cards[3].value==cards[4].value+2)
            {
                if(cards[2].value==14)return 14;
                else return cards[2].value+1;
            }
            else if(cards[3].value==cards[4].value+3)
            {
                return cards[2].value;
            }
        }
        else if(cards[2].value==cards[3].value+2)
        {
            if(cards[3].value==cards[4].value+1)
            {
                if(cards[2].value==14)return 14;
                else return cards[2].value+1;
            }
            else if(cards[3].value==cards[4].value+2)
            {
                return cards[2].value;
            }
        }
        else if(cards[2].value==cards[3].value+3&&cards[3].value==cards[4].value+1)
        {
            return cards[2].value;
        }

        if(cards[2].value==14)
        {
            cards[2].value=1;

            for(int i=2;i<5;i++)
            {
                for(int j=i+1;j<5;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[2].value==cards[3].value+1)
            {
                if(cards[3].value==cards[4].value+1)
                {
                    return cards[2].value+2;
                }
                else if(cards[3].value==cards[4].value+2)
                {
                    return cards[2].value+1;
                }
                else if(cards[3].value==cards[4].value+3)
                {
                    return cards[2].value;
                }
            }
            else if(cards[2].value==cards[3].value+2)
            {
                if(cards[3].value==cards[4].value+1)
                {
                    return cards[2].value+1;
                }
                else if(cards[3].value==cards[4].value+2)
                {
                    return cards[2].value;
                }
            }
            else if(cards[2].value==cards[3].value+3&&cards[3].value==cards[4].value+1)
            {
                return cards[2].value;
            }
        }
        return 0;
    }

    return 0;
}

//判断是否为同花顺，返回值为同花顺中最大的牌
int JudgeCards::is_straight_flush(QList<OneCard> cards)
{
    if(cards.length()!=5)return 0;

    if(cards[0].value!=15&&cards[0].color==cards[1].color&&cards[0].color==cards[2].color&&cards[0].color==cards[3].color&&cards[0].color==cards[4].color)
    {
        if(cards[0].value>15)return 0;

        if(cards[0].value==cards[1].value+1&&cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
        {
            return cards[0].value;
        }

        if(cards[0].value==14)
        {
            cards[0].value=1;\

            for(int i=0;i<5;i++)
            {
                for(int j=i+1;j<5;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[0].value==cards[1].value+1&&cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
            {
                return cards[0].value;
            }
        }
        return 0;
    }

    if(cards[0].value==15&&cards[0].color!=3&&cards[0].color==cards[1].color&&cards[0].color==cards[2].color&&cards[0].color==cards[3].color&&cards[0].color==cards[4].color)
    {
        for(int i=0;i<5;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=0;i<5;i++)
        {
            for(int j=i+1;j<5;j++)
            {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[0].value==cards[1].value+1&&cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
        {
            return cards[0].value;
        }

        if(cards[0].value==14)
        {
            cards[0].value=1;\

            for(int i=0;i<5;i++)
            {
                for(int j=i+1;j<5;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[0].value==cards[1].value+1&&cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
            {
                return cards[0].value;
            }
        }
        return 0;
    }

    if(cards[0].value==15&&cards[0].color==3&&cards[1].value!=15&&cards[1].color==cards[2].color&&cards[1].color==cards[3].color&&cards[1].color==cards[4].color)
    {
        if(cards[1].value==cards[2].value+1)
        {
            if(cards[2].value==cards[3].value+1)
            {
                if(cards[3].value==cards[4].value+1)
                {
                    if(cards[1].value==14)return cards[1].value;
                    else return cards[1].value+1;
                }
                else if(cards[3].value==cards[4].value+2)
                {
                    return cards[1].value;
                }
            }
            else if(cards[2].value==cards[3].value+2&&cards[3].value==cards[4].value+1)
            {
                return cards[1].value;
            }
        }
        else if(cards[1].value==cards[2].value+2&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
        {
            return cards[1].value;
        }

        if(cards[1].value==14)
        {
            cards[1].value=1;

            for(int i=1;i<5;i++)
            {
                for(int j=i+1;j<5;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[1].value==cards[2].value+1)
            {
                if(cards[2].value==cards[3].value+1)
                {
                    if(cards[3].value==cards[4].value+1)
                    {
                        return cards[1].value+1;
                    }
                    else if(cards[3].value==cards[4].value+2)
                    {
                        return cards[1].value;
                    }
                }
                else if(cards[2].value==cards[3].value+2&&cards[3].value==cards[4].value+1)
                {
                    return cards[1].value;
                }
            }
            else if(cards[1].value==cards[2].value+2&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
            {
                return cards[1].value;
            }
        }
        return 0;
    }

    if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color!=3&&cards[1].color==cards[2].color&&cards[1].color==cards[3].color&&cards[1].color==cards[4].color)
    {
        for(int i=1;i<5;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=1;i<5;i++)
        {
            for(int j=i+1;j<5;j++)
            {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[1].value==cards[2].value+1)
        {
            if(cards[2].value==cards[3].value+1)
            {
                if(cards[3].value==cards[4].value+1)
                {
                    if(cards[1].value==14)return cards[1].value;
                    else return cards[1].value+1;
                }
                else if(cards[3].value==cards[4].value+2)
                {
                    return cards[1].value;
                }
            }
            else if(cards[2].value==cards[3].value+2&&cards[3].value==cards[4].value+1)
            {
                return cards[1].value;
            }
        }
        else if(cards[1].value==cards[2].value+2&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
        {
            return cards[1].value;
        }

        if(cards[1].value==14)
        {
            cards[1].value=1;

            for(int i=1;i<5;i++)
            {
                for(int j=i+1;j<5;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[1].value==cards[2].value+1)
            {
                if(cards[2].value==cards[3].value+1)
                {
                    if(cards[3].value==cards[4].value+1)
                    {
                        return cards[1].value+1;
                    }
                    else if(cards[3].value==cards[4].value+2)
                    {
                        return cards[1].value;
                    }
                }
                else if(cards[2].value==cards[3].value+2&&cards[3].value==cards[4].value+1)
                {
                    return cards[1].value;
                }
            }
            else if(cards[1].value==cards[2].value+2&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1)
            {
                return cards[1].value;
            }
        }
        return 0;
    }

    if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color==3&&cards[2].color==cards[3].color&&cards[2].color==cards[4].color)
    {
        for(int i=2;i<5;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=2;i<5;i++)
        {
            for(int j=i+1;j<5;j++)
            {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[2].value==cards[3].value+1)
        {
            if(cards[3].value==cards[4].value+1)
            {
                if(cards[2].value>12)return 14;
                else return cards[2].value+2;
            }
            else if(cards[3].value==cards[4].value+2)
            {
                if(cards[2].value==14)return 14;
                else return cards[2].value+1;
            }
            else if(cards[3].value==cards[4].value+3)
            {
                return cards[2].value;
            }
        }
        else if(cards[2].value==cards[3].value+2)
        {
            if(cards[3].value==cards[4].value+1)
            {
                if(cards[2].value==14)return 14;
                else return cards[2].value+1;
            }
            else if(cards[3].value==cards[4].value+2)
            {
                return cards[2].value;
            }
        }
        else if(cards[2].value==cards[3].value+3&&cards[3].value==cards[4].value+1)
        {
            return cards[2].value;
        }

        if(cards[2].value==14)
        {
            cards[2].value=1;

            for(int i=2;i<5;i++)
            {
                for(int j=i+1;j<5;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[2].value==cards[3].value+1)
            {
                if(cards[3].value==cards[4].value+1)
                {
                    return cards[2].value+2;
                }
                else if(cards[3].value==cards[4].value+2)
                {
                    return cards[2].value+1;
                }
                else if(cards[3].value==cards[4].value+3)
                {
                    return cards[2].value;
                }
            }
            else if(cards[2].value==cards[3].value+2)
            {
                if(cards[3].value==cards[4].value+1)
                {
                    return cards[2].value+1;
                }
                else if(cards[3].value==cards[4].value+2)
                {
                    return cards[2].value;
                }
            }
            else if(cards[2].value==cards[3].value+3&&cards[3].value==cards[4].value+1)
            {
                return cards[2].value;
            }
        }
        return 0;
    }

    return 0;
}

//判断是否为三带二,返回值为三带二牌值
int JudgeCards::is_sandaier(QList<OneCard> cards)
{
    if(cards.length()!=5)return 0;

    if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color==3)
    {
        if(cards[2].value==cards[3].value&&cards[2].value!=cards[4].value)
        {
            return cards[2].value;
        }

        if(cards[2].value!=cards[3].value&&cards[3].value==cards[4].value)
        {
            return cards[3].value;
        }

        return 0;
    }

    if(cards[0].value==15&&cards[0].color==3)
    {
        if(cards[1].value==cards[2].value&&cards[1].value==cards[3].value&&cards[1].value!=cards[4].value)
        {
            return cards[1].value;
        }

        if(cards[1].value==cards[2].value&&cards[2].value!=cards[3].value&&cards[3].value==cards[4].value)
        {
            return cards[1].value;
        }

        if(cards[1].value!=cards[2].value&&cards[2].value==cards[3].value&&cards[2].value==cards[4].value)
        {
            return cards[2].value;
        }

        return 0;
    }

    if(cards[0].value==cards[1].value&&cards[0].value==cards[2].value&&cards[2].value!=cards[3].value&&cards[3].value==cards[4].value)
    {
        return cards[0].value;
    }

    if(cards[0].value==cards[1].value&&cards[1].value!=cards[2].value&&cards[2].value==cards[3].value&&cards[2].value==cards[4].value)
    {
        if(cards[0].value>15)return 0;
        return cards[2].value;
    }

    return 0;
}

//判断是否为连对，返回值为连对牌值
int JudgeCards::is_liandui(QList<OneCard> cards)
{
    if(cards.length()!=6)return 0;

    if(!(cards[0].value==15&&cards[0].color==3))
    {
        for(int i=0;i<6;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=0;i<6;i++)
        {
            for(int j=i+1;j<6;j++)
          {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp;
                    temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[0].value==cards[1].value&&cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
        {
            return cards[0].value;
        }

        if(cards[0].value==14&&cards[1].value==14)
        {
            cards[0].value=cards[1].value=1;

            for(int i=0;i<6;i++)
            {
                for(int j=i+1;j<6;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp;
                        temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[0].value==cards[1].value&&cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
            {
                return cards[0].value;
            }
        }

        return 0;
    }

    if(cards[0].value==15&&cards[0].color==3&&!(cards[1].value==15&&cards[1].color==3))
    {
        for(int i=1;i<6;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=1;i<6;i++)
        {
            for(int j=i+1;j<6;j++)
            {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp;
                    temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[1].value==cards[2].value&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value&&cards[4].value==cards[5].value+1)
        {
            return cards[1].value;
        }

        if(cards[1].value==cards[2].value&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
        {
            return cards[1].value;
        }

        if(cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
        {
            return cards[1].value;
        }

        if(cards[1].value==14)
        {
            cards[1].value=1;
            if(cards[2].value==14)cards[2].value=1;

            for(int i=1;i<6;i++)
            {
                for(int j=i+1;j<6;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp;
                        temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[1].value==cards[2].value&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value&&cards[4].value==cards[5].value+1)
            {
                return cards[1].value;
            }

            if(cards[1].value==cards[2].value&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
            {
                return cards[1].value;
            }

            if(cards[1].value==cards[2].value+1&&cards[2].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
            {
                return cards[1].value;
            }
        }

        return 0;
    }

    if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color==3)
    {
        for(int i=2;i<6;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=2;i<6;i++)
        {
            for(int j=i+1;j<6;j++)
            {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp;
                    temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[2].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
        {
            if(cards[2].value==14)return 14;
            else return cards[2].value+1;
        }

        if(cards[2].value==cards[3].value&&cards[3].value==cards[4].value+2&&cards[4].value==cards[5].value)
        {
            return cards[2].value;
        }

        if(cards[2].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value+1)
        {
             return cards[2].value;
        }

        if(cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value&&cards[4].value==cards[5].value+1)
        {
             return cards[2].value;
        }

        if(cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
        {
             return cards[2].value;
        }

        if(cards[2].value==14)
        {
            cards[2].value=1;
            if(cards[3].value==14)cards[3].value=1;

            for(int i=2;i<6;i++)
            {
                for(int j=i+1;j<6;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp;
                        temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[2].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
            {
                if(cards[2].value==14)return 14;
                else return cards[2].value+1;
            }

            if(cards[2].value==cards[3].value&&cards[3].value==cards[4].value+2&&cards[4].value==cards[5].value)
            {
                return cards[2].value;
            }

            if(cards[2].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value+1)
            {
                 return cards[2].value;
            }

            if(cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value&&cards[4].value==cards[5].value+1)
            {
                 return cards[2].value;
            }

            if(cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
            {
                 return cards[2].value;
            }
        }

        return 0;
    }

    return 0;
}

//判断是否为钢板，返回值为钢板牌值
int JudgeCards::is_gangban(QList<OneCard> cards)
{
    if(cards.length()!=6)return 0;

    if(!(cards[0].value==15&&cards[0].color==3))
    {
        for(int i=0;i<6;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=0;i<6;i++)
        {
            for(int j=i+1;j<6;j++)
          {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp;
                    temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[0].value==cards[1].value&&cards[0].value==cards[2].value&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value&&cards[3].value==cards[5].value)
        {
            return cards[0].value;
        }

        if(cards[0].value==14&&cards[1].value==14&&cards[2].value==14&&cards[3].value==2&&cards[4].value==2&&cards[5].value==2)
        {
            cards[0].value=1;
            cards[1].value=1;
            cards[2].value=1;

            for(int i=0;i<6;i++)
            {
                for(int j=i+1;j<6;j++)
              {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp;
                        temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            return cards[0].value;
        }

        return 0;
    }

    if(cards[0].value==15&&cards[0].color==3&&!(cards[1].value==15&&cards[1].color==3))
    {
        for(int i=1;i<6;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=1;i<6;i++)
        {
            for(int j=i+1;j<6;j++)
            {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp;
                    temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[1].value==cards[2].value&&cards[1].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
        {
            return cards[1].value;
        }

        if(cards[1].value==cards[2].value&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value&&cards[3].value==cards[5].value)
        {
            return cards[1].value;
        }

        if(cards[1].value==14)
        {
            cards[1].value=1;
            if(cards[2].value==14)cards[2].value=1;
            if(cards[3].value==14)cards[3].value=1;

            for(int i=1;i<6;i++)
            {
                for(int j=i+1;j<6;j++)
              {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp;
                        temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[1].value==cards[2].value&&cards[1].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
            {
                return cards[1].value;
            }

            if(cards[1].value==cards[2].value&&cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value&&cards[3].value==cards[5].value)
            {
                return cards[1].value;
            }
        }

        return 0;
    }

    if(cards[0].value==15&&cards[0].color==3&&cards[1].value==15&&cards[1].color==3)
    {
        for(int i=2;i<6;i++)
        {
            if(cards[i].value==15)cards[i].value=special_card;
        }

        for(int i=2;i<6;i++)
        {
            for(int j=i+1;j<6;j++)
            {
                if(cards[i].value<cards[j].value)
                {
                    OneCard temp;
                    temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }

        if(cards[2].value==cards[3].value&&cards[2].value==cards[4].value&&cards[4].value==cards[5].value+1)
        {
            return cards[2].value;
        }

        if(cards[2].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
        {
            return cards[2].value;
        }

        if(cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value&&cards[3].value==cards[5].value)
        {
            return cards[2].value;
        }

        if(cards[2].value==14)
        {
            cards[2].value=1;
            if(cards[3].value==14)cards[3].value=1;
            if(cards[4].value==14)cards[4].value=1;

            for(int i=2;i<6;i++)
            {
                for(int j=i+1;j<6;j++)
                {
                    if(cards[i].value<cards[j].value)
                    {
                        OneCard temp;
                        temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(cards[2].value==cards[3].value&&cards[2].value==cards[4].value&&cards[4].value==cards[5].value+1)
            {
                return cards[2].value;
            }

            if(cards[2].value==cards[3].value&&cards[3].value==cards[4].value+1&&cards[4].value==cards[5].value)
            {
                return cards[2].value;
            }

            if(cards[2].value==cards[3].value+1&&cards[3].value==cards[4].value&&cards[3].value==cards[5].value)
            {
                return cards[2].value;
            }
        }

        return 0;
    }

    return 0;
}

//判断出牌是否正确
bool JudgeCards::is_right_dis(QList<OneCard> card_before,QList<OneCard> card_now, int special_card)
{
    set_special_card(special_card);

    int before_cnt=card_before.length();
    int now_cnt=card_now.length();

    if(before_cnt==4&&is_bomb(card_before)&&card_before[0].value==17)return false;

    if(now_cnt==1)
    {
        if(before_cnt==0)return true;
        if(before_cnt==1&&card_before[0].value<card_now[0].value)return true;
        return false;
    }

    if(now_cnt==2)
    {
        if(before_cnt!=0&&before_cnt!=2)return false;

        if(card_now[0].value==card_now[1].value)
        {
            if(before_cnt==0)return true;
            if(before_cnt==2&&card_before[0].value<card_now[0].value)return true;
        }
        if(card_now[0].value==15&&card_now[0].color==3)
        {
            card_now[0].value=card_now[1].value;
            if(before_cnt==0)return true;
            if(before_cnt==2&&card_before[0].value<card_now[0].value)return true;
        }
        return false;
    }

    if(now_cnt==3)
    {
        if(before_cnt!=0&&before_cnt!=3)return false;

        if(card_now[0].value==card_now[1].value&&card_now[0].value==card_now[2].value)
        {
            if(before_cnt==0)return true;
            if(before_cnt==3&&card_before[0].value<card_now[0].value)return true;
        }
        if(card_now[0].value==15&&card_now[0].color==3&&card_now[1].value==card_now[2].value)
        {
            card_now[0].value=card_now[1].value;
            if(before_cnt==0)return true;
            if(before_cnt==3&&card_before[0].value<card_now[0].value)return true;
        }
        if(card_now[0].value==15&&card_now[0].color==3&&card_now[1].value==15&&card_now[1].color==3)
        {
            card_now[0].value=card_now[2].value;
            card_now[1].value=card_now[2].value;
            if(before_cnt==0)return true;
            if(before_cnt==3&&card_before[0].value<card_now[0].value)return true;
        }
        return false;
    }

    if(now_cnt==4&&is_bomb(card_now))
    {
        if(is_bomb(card_now)&&card_now[0].value==17)return true;

        if(!is_bomb(card_before)&&!is_straight_flush(card_before))return true;

        if(before_cnt==4&&card_before[0].value<card_now[0].value)return true;

        return false;
    }

    if(now_cnt==5)
    {

        if(is_straight_flush(card_now))
        {
            if(is_straight_flush(card_before)<is_straight_flush(card_now))return true;
            else return false;
        }

        if(is_straight_flush(card_before))return false;

        if(is_bomb(card_now))
        {
            if(!is_bomb(card_before)||before_cnt==4)return true;

            if(before_cnt==5&&card_before[0].value<card_now[0].value)return true;

            return false;
        }

        if(is_bomb(card_before))return false;

        if(is_straight(card_now))
        {
            if(before_cnt==0)return true;
            if(is_straight(card_before)&&is_straight(card_now)>is_straight(card_before))return true;
            else return false;
        }

        if(is_sandaier(card_now))
        {
            if(before_cnt==0)return true;
            if(is_sandaier(card_before)&&is_sandaier(card_now)>is_sandaier(card_before))return true;
            else return false;
        }

        return false;
    }

    if(now_cnt==6)
    {
        if(is_bomb(card_now))
        {
            if(!is_bomb(card_before))return true;

            if(before_cnt<6||(before_cnt==6&&card_before[0].value<card_now[0].value))return true;

            return false;
        }

        if(is_bomb(card_before)||is_straight_flush(card_before))return false;

        if(is_liandui(card_now))
        {
            if(before_cnt==0)return true;
            if(is_liandui(card_before)&&is_liandui(card_before)<is_liandui(card_now))return true;
            return false;
        }

        if(is_gangban(card_now))
        {
            if(before_cnt==0)return true;
            if(is_gangban(card_before)&&is_gangban(card_before)<is_gangban(card_now))return true;
            return false;
        }

        return false;
    }

    if(now_cnt==7)
    {
        if(is_bomb(card_now))
        {
            if(!is_bomb(card_before))return true;

            if(before_cnt<7||(before_cnt==7&&card_before[0].value<card_now[0].value))return true;

            return false;
        }
        else return false;
    }

    if(now_cnt==8)
    {
        if(is_bomb(card_now))
        {
            if(!is_bomb(card_before))return true;

            if(before_cnt<8||(before_cnt==8&&card_before[0].value<card_now[0].value))return true;

            return false;
        }
        else return false;
    }

    return false;
}
