#include "cardswindow.h"
#include "ui_cardswindow.h"

CardsWindow::CardsWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CardsWindow)
{
    ui->setupUi(this);

    //初始化数据
    while(1)
    {
        special_card=2;
        play_round=1;
        best_player=0;
        memset(rank,0,sizeof(rank));
        ranker=0;
        score1=2,score2=2;
        setcard_cnt=0,set_x=0;
        straight_num1=0,straight_num2=0;
        timing=30;

        break;
    }

    //将27张牌保存到数组
    while(1)
    {
        card[0]=ui->card_01;
        card[1]=ui->card_02;
        card[2]=ui->card_03;
        card[3]=ui->card_04;
        card[4]=ui->card_05;
        card[5]=ui->card_06;
        card[6]=ui->card_07;
        card[7]=ui->card_08;
        card[8]=ui->card_09;
        card[9]=ui->card_10;
        card[10]=ui->card_11;
        card[11]=ui->card_12;
        card[12]=ui->card_13;
        card[13]=ui->card_14;
        card[14]=ui->card_15;
        card[15]=ui->card_16;
        card[16]=ui->card_17;
        card[17]=ui->card_18;
        card[18]=ui->card_19;
        card[19]=ui->card_20;
        card[20]=ui->card_21;
        card[21]=ui->card_22;
        card[22]=ui->card_23;
        card[23]=ui->card_24;
        card[24]=ui->card_25;
        card[25]=ui->card_26;
        card[26]=ui->card_27;
        break;
    }

    //将出牌区8张牌保存到数组
    while(1)
    {
        dis[0]=ui->dis_1;
        dis[1]=ui->dis_2;
        dis[2]=ui->dis_3;
        dis[3]=ui->dis_4;
        dis[4]=ui->dis_5;
        dis[5]=ui->dis_6;
        dis[6]=ui->dis_7;
        dis[7]=ui->dis_8;
        break;
    }

    //将玩家名和手牌数保存到数组
    while(1)
    {
        player_name[0]=ui->player1;
        player_name[1]=ui->player2;
        player_name[2]=ui->player3;
        player_name[3]=ui->player4;

        player_number[0]=ui->player1_number;
        player_number[1]=ui->player2_number;
        player_number[2]=ui->player3_number;
        player_number[3]=ui->player4_number;

        break;
    }

    //初始化按钮
    while(1)
    {
        ui->start->setVisible(1);
        ui->discard->setVisible(0);
        ui->pass->setVisible(0);
        ui->countdown->setVisible(0);
        ui->error->setVisible(0);

        ui->jingong->setVisible(0);
        ui->huangong->setVisible(0);
        ui->jingong2->setVisible(0);
        ui->huangong2->setVisible(0);
        ui->best_player->setVisible(0);
        ui->player1_number->setVisible(0);
        ui->player2_number->setVisible(0);
        ui->player3_number->setVisible(0);
        ui->player4_number->setVisible(0);
        ui->setcard->setVisible(0);
        ui->setbackcard->setVisible(0);
        ui->straight_flush->setVisible(0);

        break;
    }

    //初始化27张牌
    for(int i=0;i<27;i++)card[i]->setVisible(0);

    //初始化出牌区8张牌
    for(int i=0;i<8;i++)dis[i]->setVisible(0);

    connect(timer,SIGNAL(timeout()),this,SLOT(timerUpDate()));
}

CardsWindow::~CardsWindow()
{
    delete ui;
}

//玩家名
QString CardsWindow::set_name(int m)
{
    if(m==1)return "南";
    if(m==2)return "东";
    if(m==3)return "北";
    if(m==4)return "西";
    return 0;
}

//用颜色替代花色
QString CardsWindow::card_color(OneCard m)//  3"♥"红色  4"♠"蓝色  5"♣"绿色  6"♦"黄色 1,2"joker"白色
{
    if(m.color==3)return "background-color:rgb(255,0,0)";
    if(m.color==4)return "background-color:rgb(0,0,255)";
    if(m.color==5)return "background-color:rgb(0,255,0)";
    if(m.color==6)return "background-color:rgb(255,255,0)";
    return "background-color:rgb(255,255,255)";
}


void CardsWindow::timerUpDate()
{
    timing--;

    if(timing<=0)emit changeplayer();
    QFont ft;ft.setPointSize(12);
    ui->countdown->setFont(ft);
    ui->countdown->setNum(timing);
}

void CardsWindow::changeplayer()
{
    if(ui->pass->isVisible())
    {
        ui->pass->click();
        return;
    }
    if(ui->discard->isVisible())
    {
        int len=cardarray[play_round-1].length();
        card[len-1]->click();
        ui->discard->click();
        return;
    }
}



void CardsWindow::on_start_clicked()
{
    straight_num1=0;
    straight_num2=0;

    ui->start->setVisible(0);

    player.shuffle_cards();
    player.make_player(cardarray,special_card);
    player.sort_player(cardarray);

    card_before.clear();
    card_now.clear();

    ui->discard->setVisible(0);
    ui->discard->move(310,250);

    for(int i=0;i<4;i++)player_number[i]->setVisible(1);
    ui->setcard->setVisible(1);
    ui->setbackcard->setVisible(1);
    ui->straight_flush->setVisible(1);

    //不需要贡牌
    if(score1==2&&score2==2)
    {
        ui->discard->setVisible(1);
        ui->countdown->setVisible(1);
        timer->start(1000);

        play_round=1;

        //设置玩家
        QFont ft;ft.setPointSize(12);
        for(int i=0,k=play_round;i<4;i++)
        {
            player_name[i]->setText(set_name(k));
            player_name[i]->setFont(ft);
            player_number[i]->setNum(cardarray[k-1].length());
            player_number[i]->setFont(ft);
            if(++k==5)k=1;
        }

        //设置牌
        for(int i=0,left_x=80;i<27;i++)
        {
            card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
            card[i]->setText(cardarray[play_round-1][i].num);
            card[i]->move(left_x+i*20,300);
            card[i]->setChecked(0);
            card[i]->setVisible(1);
        }

        ranker=0;
        memset(rank,0,sizeof(rank));

        return;
    }

    //需要贡牌
    if(ranker==2&&(rank[0]+rank[1])%2==0)
    {
        //抗贡
        if((cardarray[rank[2]-1][0].value==17&&cardarray[rank[3]-1][0].value==17)||(cardarray[rank[2]-1][0].value==17&&cardarray[rank[2]-1][1].value==17)||(cardarray[rank[3]-1][0].value==17&&cardarray[rank[3]-1][1].value==17))
        {
            ui->discard->setVisible(1);
            ui->countdown->setVisible(1);
            timer->start(1000);

            play_round=rank[0];

            //设置玩家
            QFont ft;ft.setPointSize(12);
            for(int i=0,k=play_round;i<4;i++)
            {
                player_name[i]->setText(set_name(k));
                player_name[i]->setFont(ft);
                player_number[i]->setNum(cardarray[k-1].length());
                player_number[i]->setFont(ft);
                if(++k==5)k=1;
            }

            //设置牌
            for(int i=0,left_x=80;i<27;i++)
            {
                card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
                card[i]->setText(cardarray[play_round-1][i].num);
                card[i]->move(left_x+i*20,300);
                card[i]->setChecked(0);
                card[i]->setVisible(1);
            }

            ranker=0;
            memset(rank,0,sizeof(rank));
            return;
        }

        play_round=rank[3];

        //设置玩家
        QFont ft;ft.setPointSize(12);
        for(int i=0,k=play_round;i<4;i++)
        {
            player_name[i]->setText(set_name(k));
            player_name[i]->setFont(ft);
            player_number[i]->setNum(cardarray[k-1].length());
            player_number[i]->setFont(ft);
            if(++k==5)k=1;
        }

        //设置牌
        for(int i=0,left_x=80;i<27;i++)
        {
            card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
            card[i]->setText(cardarray[play_round-1][i].num);
            card[i]->move(left_x+i*20,300);
            card[i]->setChecked(0);
            card[i]->setEnabled(0);
            card[i]->setVisible(1);
        }

        //设置最大的牌可选,最多八张
        int k=0;
        while(cardarray[play_round-1][k].value==cardarray[play_round-1][k+1].value)k++;
        k++;
        for(int i=0;i<k;i++)card[i]->setEnabled(1);

        ui->jingong->setVisible(1);
    }

    if(ranker==3&&(rank[0]+rank[2])%2==0)
    {
        //抗贡
        if(cardarray[rank[3]-1][0].value==17&&cardarray[rank[3]-1][1].value==17)
        {
            play_round=rank[0];

            ui->discard->setVisible(1);
            ui->countdown->setVisible(1);
            timer->start(1000);

            //设置玩家
            QFont ft;ft.setPointSize(12);
            for(int i=0,k=play_round;i<4;i++)
            {
                player_name[i]->setText(set_name(k));
                player_name[i]->setFont(ft);
                player_number[i]->setNum(cardarray[k-1].length());
                player_number[i]->setFont(ft);
                if(++k==5)k=1;
            }

            //设置牌
            for(int i=0,left_x=80;i<27;i++)
            {
                card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
                card[i]->setText(cardarray[play_round-1][i].num);
                card[i]->move(left_x+i*20,300);
                card[i]->setChecked(0);
                card[i]->setVisible(1);
            }

            ranker=0;
            memset(rank,0,sizeof(rank));

            return;
        }

        play_round=rank[3];

        //设置玩家
        QFont ft;ft.setPointSize(12);
        for(int i=0,k=play_round;i<4;i++)
        {
            player_name[i]->setText(set_name(k));
            player_name[i]->setFont(ft);
            player_number[i]->setNum(cardarray[k-1].length());
            player_number[i]->setFont(ft);
            if(++k==5)k=1;
        }

        //设置牌
        for(int i=0,left_x=80;i<27;i++)
        {
            card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
            card[i]->setText(cardarray[play_round-1][i].num);
            card[i]->move(left_x+i*20,300);
            card[i]->setChecked(0);
            card[i]->setEnabled(0);
            card[i]->setVisible(1);
        }

        //设置最大的牌可选,最多八张
        int k=0;
        while(cardarray[play_round-1][k].value==cardarray[play_round-1][k+1].value)k++;
        k++;
        for(int i=0;i<k;i++)card[i]->setEnabled(1);

        ui->jingong->setVisible(1);
    }

    if(ranker==3&&(rank[1]+rank[2])%2==0)
    {
        play_round=rank[3];

        //设置玩家
        QFont ft;ft.setPointSize(12);
        for(int i=0,k=play_round;i<4;i++)
        {
            player_name[i]->setText(set_name(k));
            player_name[i]->setFont(ft);
            player_number[i]->setNum(cardarray[k-1].length());
            player_number[i]->setFont(ft);
            if(++k==5)k=1;
        }

        //设置牌
        for(int i=0,left_x=80;i<27;i++)
        {
            card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
            card[i]->setText(cardarray[play_round-1][i].num);
            card[i]->move(left_x+i*20,300);
            card[i]->setChecked(0);
            card[i]->setVisible(1);
        }

        //设置最大的牌可选,最多八张
        int k=0;
        while(cardarray[play_round-1][k].value==cardarray[play_round-1][k+1].value)k++;
        k++;
        for(int i=0;i<k;i++)card[i]->setEnabled(1);

        ui->jingong->setVisible(1);
    }

}

void CardsWindow::on_discard_clicked()
{
    card_now.clear();
    set_x=0;
    straight_num1=0;
    straight_num2=0;

    int card_number=cardarray[play_round-1].length();

    //将选中的牌加入card_now
    for(int i=0,j=0;j<card_number;i++,j++)if(card[i]->isChecked())card_now.append(cardarray[play_round-1][i]);

    //如果出牌错误，整理牌面，提示错误
    if(judgecards.is_right_dis(card_before,card_now,special_card)==false)
    {
        for(int i=0,j=0;j<card_number;i++,j++)
        {
            if(card[i]->isChecked())
            {
                card[i]->setChecked(0);
                int xx=card[i]->x(),yy=card[i]->y();
                card[i]->move(xx,yy+30);
            }
        }

        card_now.clear();

        //提示出牌错误
        ui->error->setVisible(1);

        return;
    }

    //如果出牌正确，设置button位置
    ui->error->setVisible(0);
    ui->pass->setVisible(1);
    ui->pass->move(250,250);
    ui->discard->move(370,250);
    timing=30;
    QFont font;font.setPointSize(12);
    ui->countdown->setFont(font);
    ui->countdown->setNum(timing);

    //更新card_before
    for(int i=0;i<8;i++)dis[i]->setVisible(0);

    best_player=play_round;
    ui->best_player->setVisible(1);
    font.setPointSize(12);
    ui->best_player->setText(set_name(best_player));
    ui->best_player->setFont(font);

    card_before.clear();
    card_before=card_now;

    //将出的牌从cardarray中删去
    for(int i=0,j=0;j<card_number;i++,j++)if(card[j]->isChecked())cardarray[play_round-1].removeAt(i--);

    //将出的牌放到出牌区域
    int dis_x=mid_x-card_now.length()*10;
    int dis_y=100;

    for(int i=0;i<card_now.length();i++)
    {
        dis[i]->setStyleSheet(card_color(card_now[i]));
        dis[i]->setText(card_now[i].num);
        dis[i]->move(dis_x+i*20,dis_y);
        dis[i]->setVisible(1);
    }

    font.setPointSize(24);
    //如果牌已经出完，标记
    if(cardarray[play_round-1].length()==0)rank[ranker++]=play_round;

    //1 1 0 0
    if(ranker==2&&(rank[0]+rank[1])%2==0)
    {
        if(rank[0]==1)
        {
            score1+=3;
            rank[1]=3;
            rank[2]=2;
            rank[3]=4;
        }
        if(rank[0]==2)
        {
            score2+=3;
            rank[1]=4;
            rank[2]=1;
            rank[3]=3;
        }
        if(rank[0]==3)
        {
            score1+=3;
            rank[1]=1;
            rank[2]=2;
            rank[3]=4;
        }
        if(rank[0]==4)
        {
            score2+=3;
            rank[1]=2;
            rank[2]=3;
            rank[3]=1;
        }

        if(score1>9||score2>9)score1=score2=2;

        ui->score1->setNum(score1);
        ui->score1->setFont(font);
        ui->score2->setNum(score2);
        ui->score2->setFont(font);

        special_card=score1>score2?score1:score2;

        while(1)
        {
            ui->start->setVisible(1);
            ui->best_player->setVisible(0);
            ui->discard->setVisible(0);
            ui->pass->setVisible(0);
            ui->countdown->setVisible(0);
            ui->error->setVisible(0);
            for(int i=0;i<4;i++)player_number[i]->setVisible(0);
            ui->setcard->setVisible(0);
            ui->setbackcard->setVisible(0);
            ui->straight_flush->setVisible(0);

            break;
        }


        for(int i=0;i<27;i++)card[i]->setVisible(0);
        for(int i=0;i<8;i++)dis[i]->setVisible(0);

        timer->stop();
        timing=30;
        for(int i=0;i<4;i++)cardarray[i].clear();
        return;
    }

    //1 0 1 0
    if(ranker==3&&(rank[0]+rank[2])%2==0)
    {
        if(rank[1]==1)
        {
            score2+=2;
            rank[3]=3;
        }
        if(rank[1]==2)
        {
            score1+=2;
            rank[3]=4;
        }
        if(rank[1]==3)
        {
            score2+=2;
            rank[3]=1;
        }
        if(rank[1]==4)
        {
            score1+=2;
            rank[3]=2;
        }
        if(score1>9||score2>9)score1=score2=2;

        ui->score1->setNum(score1);
        ui->score1->setFont(font);
        ui->score2->setNum(score2);
        ui->score2->setFont(font);

        special_card=score1>score2?score1:score2;

        while(1)
        {
            ui->start->setVisible(1);
            ui->best_player->setVisible(0);
            ui->discard->setVisible(0);
            ui->pass->setVisible(0);
            ui->countdown->setVisible(0);
            ui->error->setVisible(0);
            for(int i=0;i<4;i++)player_number[i]->setVisible(0);
            ui->setcard->setVisible(0);
            ui->setbackcard->setVisible(0);
            ui->straight_flush->setVisible(0);

            break;
        }

        for(int i=0;i<27;i++)card[i]->setVisible(0);
        for(int i=0;i<8;i++)dis[i]->setVisible(0);

        timer->stop();
        timing=30;
        for(int i=0;i<4;i++)cardarray[i].clear();
        return;
    }

    //1 0 0 1
    if(ranker==3&&(rank[1]+rank[2])%2==0)
    {
        if(rank[0]==1)
        {
            score1+=1;
            rank[3]=3;
        }
        if(rank[0]==2)
        {
            score2+=1;
            rank[3]=4;
        }
        if(rank[0]==3)
        {
            score1+=1;
            rank[3]=1;
        }
        if(rank[0]==4)
        {
            score2+=1;
            rank[3]=2;
        }

        if(score1>9||score2>9)score1=score2=2;

        ui->score1->setNum(score1);
        ui->score1->setFont(font);
        ui->score2->setNum(score2);
        ui->score2->setFont(font);

        special_card=score1>score2?score1:score2;

        while(1)
        {
            ui->start->setVisible(1);
            ui->best_player->setVisible(0);
            ui->discard->setVisible(0);
            ui->pass->setVisible(0);
            ui->countdown->setVisible(0);
            ui->error->setVisible(0);
            for(int i=0;i<4;i++)player_number[i]->setVisible(0);
            ui->setcard->setVisible(0);
            ui->setbackcard->setVisible(0);
            ui->straight_flush->setVisible(0);

            break;
        }

        for(int i=0;i<27;i++)card[i]->setVisible(0);
        for(int i=0;i<8;i++)dis[i]->setVisible(0);

        timer->stop();
        timing=30;
        for(int i=0;i<4;i++)cardarray[i].clear();
        return;
    }

    //切换玩家
    for(int i=0;i<27;i++)
    {
        card[i]->setChecked(0);
        card[i]->setVisible(0);
    }

    if(++play_round==5)play_round=1;

    while(cardarray[play_round-1].length()==0)if(++play_round==5)play_round=1;

    //设置玩家名和手牌数
    QFont ft;ft.setPointSize(12);
    for(int i=0,k=play_round;i<4;i++)
    {
        player_name[i]->setText(set_name(k));
        player_name[i]->setFont(ft);
        player_number[i]->setNum(cardarray[k-1].length());
        player_number[i]->setFont(ft);
        if(++k==5)k=1;
    }

    //设置玩家手牌
    int card_len=cardarray[play_round-1].length();
    int left_x=mid_x-card_len*10;
    for(int i=0;i<card_len;i++)
    {
        card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
        card[i]->setText(cardarray[play_round-1][i].num);
        card[i]->move(left_x+i*20,300);
        card[i]->setVisible(1);
    }
}

void CardsWindow::on_pass_clicked()
{
    timing=30;
    QFont font;font.setPointSize(12);
    ui->countdown->setFont(font);
    ui->countdown->setNum(timing);

    ui->error->setVisible(0);
    set_x=0;
    straight_num1=0;
    straight_num2=0;

    //切换玩家
    for(int i=0;i<27;i++)
    {
        card[i]->setVisible(0);
        card[i]->setChecked(0);
    }

    if(++play_round==5)play_round=1;

    while(cardarray[play_round-1].length()==0)
    {
        if(play_round==best_player)
        {
            card_before.clear();
            for(int i=0;i<8;i++)dis[i]->setVisible(0);

            ui->pass->setVisible(0);
            ui->best_player->setVisible(0);

            ui->discard->move(310,250);

            //切换到对家
            play_round+=2;
            if(play_round>4)play_round-=4;

            break;
        }

        if(++play_round==5)play_round=1;
    }

    if(play_round==best_player)
    {
        card_before.clear();
        for(int i=0;i<8;i++)dis[i]->setVisible(0);

        ui->pass->setVisible(0);
        ui->best_player->setVisible(0);

        ui->discard->move(310,250);
    }

    //设置玩家名和手牌数
    QFont ft;ft.setPointSize(12);
    for(int i=0,k=play_round;i<4;i++)
    {
        player_name[i]->setText(set_name(k));
        player_name[i]->setFont(ft);
        player_number[i]->setNum(cardarray[k-1].length());
        player_number[i]->setFont(ft);
        if(++k==5)k=1;
    }

    //设置玩家手牌
    int card_len=cardarray[play_round-1].length();
    int left_x=mid_x-card_len*10;
    for(int i=0;i<card_len;i++)
    {
        card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
        card[i]->setText(cardarray[play_round-1][i].num);
        card[i]->move(left_x+i*20,300);
        card[i]->setVisible(1);
    }
}

void CardsWindow::on_jingong_clicked()
{
    ui->error->setVisible(0);

    //判断是否只选了一张牌
    int k=0;
    for(int i=0;i<8;i++)if(card[i]->isChecked())k++;

    //若不是，提示错误
    if(k!=1)
    {
        ui->error->setVisible(1);

        for(int i=0;i<8;i++)
        {
            if(card[i]->isChecked())
            {
                card[i]->setChecked(0);
                int xx=card[i]->x(),yy=card[i]->y();
                card[i]->move(xx,yy+30);
            }
        }

        return;
    }

    //将所选贡牌打出
    for(int i=0;i<8;i++)
    {
        if(card[i]->isChecked())
        {
            card[i]->setChecked(0);
            dis[0]->setStyleSheet(card_color(cardarray[play_round-1][i]));
            dis[0]->setText(cardarray[play_round-1][i].num);
            dis[0]->move(340,100);
            dis[0]->setVisible(1);
            gong_card=cardarray[play_round-1][i];
            cardarray[play_round-1].removeAt(i);
            break;
        }
    }

    //还贡
    play_round=rank[0];

    //设置玩家名和手牌数
    QFont ft;ft.setPointSize(12);
    for(int i=0,k=play_round;i<4;i++)
    {
        player_name[i]->setText(set_name(k));
        player_name[i]->setFont(ft);
        player_number[i]->setNum(cardarray[k-1].length());
        player_number[i]->setFont(ft);
        if(++k==5)k=1;
    }

    //设置玩家手牌
    int card_len=cardarray[play_round-1].length();
    int left_x=mid_x-card_len*10;
    for(int i=0;i<card_len;i++)
    {
        card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
        card[i]->setText(cardarray[play_round-1][i].num);
        card[i]->move(left_x+i*20,300);
        card[i]->setVisible(1);
        card[i]->setEnabled(1);
    }

    //设置大于10的牌不可选
    for(int i=0;i<27;i++)
    {
        if(cardarray[play_round-1][i].value<=10)break;
        card[i]->setEnabled(0);
    }

    ui->jingong->setVisible(0);
    ui->huangong->setVisible(1);

}

void CardsWindow::on_huangong_clicked()
{
    ui->error->setVisible(0);

    //判断是否只选了一张牌
    int k=0;
    for(int i=0;i<27;i++)if(card[i]->isChecked())k++;

    //若不是，提示错误
    if(k!=1)
    {
        ui->error->setVisible(1);

        for(int i=0;i<27;i++)
        {
            if(card[i]->isChecked())
            {
                card[i]->setChecked(0);
                int xx=card[i]->x(),yy=card[i]->y();
                card[i]->move(xx,yy+30);
            }
        }

        return;
    }

    //将所选还贡牌打出
    for(int i=0;i<27;i++)
    {
        if(card[i]->isChecked())
        {
            card[i]->setChecked(0);
            dis[0]->setStyleSheet(card_color(cardarray[play_round-1][i]));
            dis[0]->setText(cardarray[play_round-1][i].num);
            dis[0]->move(340,100);
            dis[0]->setVisible(1);
            huan_card=cardarray[play_round-1][i];
            cardarray[play_round-1].removeAt(i);
            break;
        }
    }

    ui->huangong->setVisible(0);

    cardarray[rank[0]-1].append(gong_card);
    cardarray[rank[3]-1].append(huan_card);

    for(int i=0;i<27;i++)
    {
        for(int j=i+1;j<27;j++)
        {
            if(cardarray[rank[0]-1][i].value<cardarray[rank[0]-1][j].value||(cardarray[rank[0]-1][i].value==cardarray[rank[0]-1][j].value&&cardarray[rank[0]-1][i].color>cardarray[rank[0]-1][j].color))
            {
                OneCard temp=cardarray[rank[0]-1][i];
                cardarray[rank[0]-1][i]=cardarray[rank[0]-1][j];
                cardarray[rank[0]-1][j]=temp;
            }
        }
    }

    for(int i=0;i<27;i++)
    {
        for(int j=i+1;j<27;j++)
        {
            if(cardarray[rank[3]-1][i].value<cardarray[rank[3]-1][j].value||(cardarray[rank[3]-1][i].value==cardarray[rank[3]-1][j].value&&cardarray[rank[3]-1][i].color>cardarray[rank[3]-1][j].color))
            {
                OneCard temp=cardarray[rank[3]-1][i];
                cardarray[rank[3]-1][i]=cardarray[rank[3]-1][j];
                cardarray[rank[3]-1][j]=temp;
            }
        }
    }

    //如果为 1 1 0 0 继续贡牌
    if(ranker==2&&(rank[0]+rank[1])%2==0)
    {
        play_round=rank[2];

        //设置玩家名和手牌数
        QFont ft;ft.setPointSize(12);
        for(int i=0,k=play_round;i<4;i++)
        {
            player_name[i]->setText(set_name(k));
            player_name[i]->setFont(ft);
            player_number[i]->setNum(cardarray[k-1].length());
            player_number[i]->setFont(ft);
            if(++k==5)k=1;
        }

        //设置玩家手牌
        int card_len=cardarray[play_round-1].length();
        int left_x=mid_x-card_len*10;
        for(int i=0;i<card_len;i++)
        {
            card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
            card[i]->setText(cardarray[play_round-1][i].num);
            card[i]->move(left_x+i*20,300);
            card[i]->setChecked(0);
            card[i]->setEnabled(0);
            card[i]->setVisible(1);
        }

       //设置最大的牌可选,最多八张
        int k=0;
        while(cardarray[play_round-1][k].value==cardarray[play_round-1][k+1].value)k++;
        k++;
        for(int i=0;i<k;i++)card[i]->setEnabled(1);

        ui->jingong2->setVisible(1);

        return;
    }

    //否则 开始出牌

    play_round=rank[3];

    ui->discard->setVisible(1);
    ui->countdown->setVisible(1);
    timer->start(1000);

    //设置玩家名和手牌数
    QFont ft;ft.setPointSize(12);
    for(int i=0,k=play_round;i<4;i++)
    {
        player_name[i]->setText(set_name(k));
        player_name[i]->setFont(ft);
        player_number[i]->setNum(cardarray[k-1].length());
        player_number[i]->setFont(ft);
        if(++k==5)k=1;
    }

    //设置玩家手牌
    int card_len=cardarray[play_round-1].length();
    int left_x=mid_x-card_len*10;
    for(int i=0;i<card_len;i++)
    {
        card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
        card[i]->setText(cardarray[play_round-1][i].num);
        card[i]->move(left_x+i*20,300);
        card[i]->setChecked(0);
        card[i]->setEnabled(1);
        card[i]->setVisible(1);
    }

    ranker=0;
    memset(rank,0,sizeof(rank));
}

void CardsWindow::on_jingong2_clicked()
{
    ui->error->setVisible(0);

    //判断是否只选了一张牌
    int k=0;
    for(int i=0;i<8;i++)if(card[i]->isChecked())k++;

    //若不是，提示错误
    if(k!=1)
    {
        ui->error->setVisible(1);

        for(int i=0;i<8;i++)
        {
            if(card[i]->isChecked())
            {
                card[i]->setChecked(0);
                int xx=card[i]->x(),yy=card[i]->y();
                card[i]->move(xx,yy+30);
            }
        }

        return;
    }

    //将所选贡牌打出
    for(int i=0;i<8;i++)
    {
        if(card[i]->isChecked())
        {
            card[i]->setChecked(0);
            dis[0]->setStyleSheet(card_color(cardarray[play_round-1][i]));
            dis[0]->setText(cardarray[play_round-1][i].num);
            dis[0]->move(340,100);
            dis[0]->setVisible(1);
            gong_card=cardarray[play_round-1][i];
            cardarray[play_round-1].removeAt(i);
            break;
        }
    }

    //还贡
    play_round=rank[1];

    //设置玩家名和手牌数
    QFont ft;ft.setPointSize(12);
    for(int i=0,k=play_round;i<4;i++)
    {
        player_name[i]->setText(set_name(k));
        player_name[i]->setFont(ft);
        player_number[i]->setNum(cardarray[k-1].length());
        player_number[i]->setFont(ft);
        if(++k==5)k=1;
    }

    //设置玩家手牌
    int card_len=cardarray[play_round-1].length();
    int left_x=mid_x-card_len*10;
    for(int i=0;i<card_len;i++)
    {
        card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
        card[i]->setText(cardarray[play_round-1][i].num);
        card[i]->move(left_x+i*20,300);
        card[i]->setVisible(1);
        card[i]->setEnabled(1);
    }

    //设置大于10的牌不可选
    for(int i=0;i<27;i++)
    {
        if(cardarray[play_round-1][i].value<=10)break;
        card[i]->setEnabled(0);
    }

    ui->jingong2->setVisible(0);
    ui->huangong2->setVisible(1);

}

void CardsWindow::on_huangong2_clicked()
{
    ui->error->setVisible(0);

    //判断是否只选了一张牌
    int k=0;
    for(int i=0;i<27;i++)if(card[i]->isChecked())k++;

    //若不是，提示错误
    if(k!=1)
    {
        ui->error->setVisible(1);

        for(int i=0;i<27;i++)
        {
            if(card[i]->isChecked())
            {
                card[i]->setChecked(0);
                int xx=card[i]->x(),yy=card[i]->y();
                card[i]->move(xx,yy+30);
            }
        }

        return;
    }

    //将所选还贡牌打出
    for(int i=0;i<27;i++)
    {
        if(card[i]->isChecked())
        {
            card[i]->setChecked(0);
            dis[0]->setStyleSheet(card_color(cardarray[play_round-1][i]));
            dis[0]->setText(cardarray[play_round-1][i].num);
            dis[0]->move(340,100);
            dis[0]->setVisible(1);
            huan_card=cardarray[play_round-1][i];
            cardarray[play_round-1].removeAt(i);
            break;
        }
    }

    ui->huangong2->setVisible(0);

    //交换牌之后开始出牌
    cardarray[rank[1]-1].append(gong_card);
    cardarray[rank[2]-1].append(huan_card);

    for(int i=0;i<27;i++)
    {
        for(int j=i+1;j<27;j++)
        {
            if(cardarray[rank[1]-1][i].value<cardarray[rank[1]-1][j].value||(cardarray[rank[1]-1][i].value==cardarray[rank[1]-1][j].value&&cardarray[rank[1]-1][i].color>cardarray[rank[1]-1][j].color))
            {
                OneCard temp=cardarray[rank[1]-1][i];
                cardarray[rank[1]-1][i]=cardarray[rank[1]-1][j];
                cardarray[rank[1]-1][j]=temp;
            }
        }
    }

    for(int i=0;i<27;i++)
    {
        for(int j=i+1;j<27;j++)
        {
            if(cardarray[rank[1]-1][i].value<cardarray[rank[2]-1][j].value||(cardarray[rank[2]-1][i].value==cardarray[rank[2]-1][j].value&&cardarray[rank[3]-1][i].color>cardarray[rank[2]-1][j].color))
            {
                OneCard temp=cardarray[rank[1]-1][i];
                cardarray[rank[1]-1][i]=cardarray[rank[1]-1][j];
                cardarray[rank[1]-1][j]=temp;
            }
        }
    }

    play_round=rank[3];

    ui->discard->setVisible(1);
    ui->countdown->setVisible(1);
    timer->start(1000);

    //设置玩家名和手牌数
    QFont ft;ft.setPointSize(12);
    for(int i=0,k=play_round;i<4;i++)
    {
        player_name[i]->setText(set_name(k));
        player_name[i]->setFont(ft);
        player_number[i]->setNum(cardarray[k-1].length());
        player_number[i]->setFont(ft);
        if(++k==5)k=1;
    }

    //设置玩家手牌
    int card_len=cardarray[play_round-1].length();
    int left_x=mid_x-card_len*10;
    for(int i=0;i<card_len;i++)
    {
        card[i]->setStyleSheet(card_color(cardarray[play_round-1][i]));
        card[i]->setText(cardarray[play_round-1][i].num);
        card[i]->move(left_x+i*20,300);
        card[i]->setChecked(0);
        card[i]->setEnabled(1);
        card[i]->setVisible(1);
    }

    ranker=0;
    memset(rank,0,sizeof(rank));
}

void CardsWindow::on_setcard_clicked()
{
    if(set_x==0)set_x=ui->card_01->x()-20;
    int set_y=300;

    //统计选中的牌数量
    for(int i=0;i<27;i++)if(card[i]->isChecked()&&card[i]->x()>set_x)setcard_cnt++;

    //整理后改变牌的位置
    int card_left=set_x+20*(setcard_cnt+1);
    for(int i=0,j=0,k=0;i<27;i++)
    {
        if(card[i]->x()>set_x)
        {
            if(card[i]->isChecked())
            {
                card[i]->setChecked(0);
                card[i]->move(set_x+20*j,set_y);
                j++;
            }
            else
            {
                card[i]->move(card_left+20*k,set_y);
                k++;
            }
        }
    }

    for(int i=0;i<cardarray[play_round-1].length();i++)
    {
        if(card[i]->isChecked())
        {
            card[i]->setChecked(0);
            int xx=card[i]->x(),yy=card[i]->y();
            card[i]->move(xx,yy+30);
        }
    }

    setcard_cnt=0;
    set_x=card_left-20;
}

void CardsWindow::on_setbackcard_clicked()
{
    set_x=0;
    int set_y=300;

    int left_x=mid_x-cardarray[play_round-1].length()*10;
    for(int i=0;i<cardarray[play_round-1].length();i++)
    {
        card[i]->move(left_x+i*20,set_y);
        card[i]->setChecked(0);
        card[i]->setVisible(1);
    }
}

void CardsWindow::on_straight_flush_clicked()
{
    int len=cardarray[play_round-1].length();
    for(int i=0;i<len;i++)
    {
        if(card[i]->isChecked())
        {
            card[i]->setChecked(0);
            int xx=card[i]->x(),yy=card[i]->y();
            card[i]->move(xx,yy+30);
        }
    }

    QList<OneCard> cards=cardarray[play_round-1];
    int st[5],k=4,flag=0,special_cnt=0;
    memset(st,0,sizeof(st));

    for(int i=0,j=0;j<len;j++)
    {
        if(cards[i].value>15)
        {
            cards.removeAt(i);
            continue;
        }
        if(cards[i].value==15&&cards[i].color==3)
        {
            special_cnt++;
            i++;   
            continue;
        }
        if(cards[i].value==15&&cards[i].color!=3)
        {
            cards[i].value=special_card;
            i++;
            flag=1;
            continue;
        }
    }

    len=cards.length();

    if(flag)
    {
        for(int i=0;i<len;i++)
        {
            for(int j=i+1;j<len;j++)
            {
                if(cards[i].value<cards[j].value||(cards[i].value==cards[j].value&&cards[i].color>cards[j].color))
                {
                    OneCard temp=cards[i];
                    cards[i]=cards[j];
                    cards[j]=temp;
                }
            }
        }
    }

    int n=special_cnt;
    int yes=0;
    int color,h;
    while(1)
    {
        if(straight_num2)break;
        if(straight_num1)
        {
            h=straight_num1-1;
            while(cards[h].value==cards[h+1].value&&cards[h].color==cards[h+1].color)h--;
        }
        else h=len-1;
        for(;h>=special_cnt;h--)
        {
            special_cnt=n;
            k=4;
            st[k--]=cards[h].value;
            color=cards[h].color;
            for(int i=h,j=h-1;j>=special_cnt;j--)
            {
                if(cards[j].color!=cards[i].color||cards[j].value==cards[i].value)continue;

                if(cards[j].value==cards[i].value+1)
                {
                    st[k--]=cards[j].value;
                    if(k<0)
                    {
                        yes=1;
                        break;
                    }
                    i=j;continue;
                }

                if(cards[j].value==cards[i].value+2)
                {
                    if(special_cnt==0)break;
                    else
                    {
                        if(k==0)
                        {
                            st[k--]=15;
                            special_cnt--;
                            yes=1;
                            break;
                        }
                        if(k>0)
                        {
                            st[k--]=15;
                            st[k--]=cards[j].value;
                            special_cnt--;
                            if(k<0)
                            {
                                yes=1;
                                break;
                            }
                            i=j;continue;
                        }
                    }
                }

                if(cards[j].value==cards[i].value+3)
                {
                    if(special_cnt==0)break;
                    if(special_cnt==1)
                    {
                        if(k==0)
                        {
                            st[k--]=15;
                            special_cnt--;
                            yes=1;
                            break;
                        }
                        else break;
                    }
                    if(special_cnt==2)
                    {
                        if(k==0)
                        {
                            st[k--]=15;
                            special_cnt--;
                            yes=1;
                            break;
                        }
                        if(k==1)
                        {
                            st[k--]=15;
                            st[k--]=15;
                            special_cnt-=2;
                            yes=1;
                            break;
                        }
                        if(k>1)
                        {
                            st[k--]=15;
                            st[k--]=15;
                            st[k--]=cards[j].value;
                            special_cnt-=2;
                            if(k<0)
                            {
                                yes=1;
                                break;
                            }
                            i=j;continue;
                        }
                    }
                }

                if(cards[j].value>cards[i].value+3)
                {
                    if(special_cnt==0)break;
                    if(special_cnt==1)
                    {
                        if(k==0)
                        {
                            st[k--]=15;
                            special_cnt--;
                            yes=1;
                            break;
                        }
                        else break;
                    }
                    if(special_cnt==2)
                    {
                        if(k==0)
                        {
                            st[k--]=15;
                            special_cnt--;
                            yes=1;
                            break;
                        }
                        if(k==1)
                        {
                            st[k--]=15;
                            st[k--]=15;
                            special_cnt-=2;
                            yes=1;
                            break;
                        }
                        else break;
                    }
                }

                else break;
            }

            if(k==1&&special_cnt==2)
            {
                st[0]=15;
                st[1]=15;
                special_cnt=0;
                yes=1;
            }

            if(k==0&&special_cnt)
            {
                st[0]=15;
                special_cnt--;
                yes=1;
            }

            if(yes)break;
        }

        break;
    }

    if(yes)straight_num1=h;
    else
    {
        straight_num1=0;
        flag=0;

        for(int i=0;i<len;i++)
        {
            if(cards[i].value==14)
            {
                cards[i].value=1;
                flag++;
            }
        }

        if(flag==0)
        {
            straight_num2=0;
            return;
        }
        else
        {
            for(int i=0;i<len;i++)
            {
                for(int j=i+1;j<len;j++)
                {
                    if(cards[i].value<cards[j].value||(cards[i].value==cards[j].value&&cards[i].color>cards[j].color))
                    {
                        OneCard temp=cards[i];
                        cards[i]=cards[j];
                        cards[j]=temp;
                    }
                }
            }

            if(straight_num2)
            {
                h=straight_num2-1;
                while(cards[h].value==cards[h+1].value&&cards[h].color==cards[h+1].color)h--;
            }
            else h=len-1;
            for(;h>=len-flag;h--)
            {
                special_cnt=n;
                k=4;
                st[k--]=cards[h].value;
                color=cards[h].color;
                for(int i=h,j=h-1;j>=special_cnt;j--)
                {
                    if(cards[j].color!=cards[i].color||cards[j].value==cards[i].value)continue;

                    if(cards[j].value==cards[i].value+1)
                    {
                        st[k--]=cards[j].value;
                        if(k<0)
                        {
                            yes=1;
                            break;
                        }
                        i=j;continue;
                    }

                    if(cards[j].value==cards[i].value+2)
                    {
                        if(special_cnt==0)break;
                        else
                        {
                            if(k==0)
                            {
                                st[k--]=15;
                                special_cnt--;
                                yes=1;
                                break;
                            }
                            if(k>0)
                            {
                                st[k--]=15;
                                st[k--]=cards[j].value;
                                special_cnt--;
                                if(k<0)
                                {
                                    yes=1;
                                    break;
                                }
                                i=j;continue;
                            }
                        }
                    }

                    if(cards[j].value==cards[i].value+3)
                    {
                        if(special_cnt==0)break;
                        if(special_cnt==1)
                        {
                            if(k==0)
                            {
                                st[k--]=15;
                                special_cnt--;
                                yes=1;
                                break;
                            }
                            else break;
                        }
                        if(special_cnt==2)
                        {
                            if(k==0)
                            {
                                st[k--]=15;
                                special_cnt--;
                                yes=1;
                                break;
                            }
                            if(k==1)
                            {
                                st[k--]=15;
                                st[k--]=15;
                                special_cnt-=2;
                                yes=1;
                                break;
                            }
                            if(k>1)
                            {
                                st[k--]=15;
                                st[k--]=15;
                                st[k--]=cards[j].value;
                                special_cnt-=2;
                                if(k<0)
                                {
                                    yes=1;
                                    break;
                                }
                                i=j;continue;
                            }
                        }
                    }

                    if(cards[j].value>cards[i].value+3)
                    {
                        if(special_cnt==0)break;
                        if(special_cnt==1)
                        {
                            if(k==0)
                            {
                                st[k--]=15;
                                special_cnt--;
                                yes=1;
                                break;
                            }
                            else break;
                        }
                        if(special_cnt==2)
                        {
                            if(k==0)
                            {
                                st[k--]=15;
                                special_cnt--;
                                yes=1;
                                break;
                            }
                            if(k==1)
                            {
                                st[k--]=15;
                                st[k--]=15;
                                special_cnt-=2;
                                yes=1;
                                break;
                            }
                            else break;
                        }
                    }

                    else break;
                }

                if(k==0&&special_cnt>0)
                {
                    st[0]=15;
                    special_cnt--;
                    yes=1;
                }

                if(k==1&&special_cnt==2)
                {
                    st[0]=15;
                    st[1]=15;
                    special_cnt=0;
                    yes=1;
                }

                if(yes)break;
            }
            if(yes)straight_num2=h;
            else
            {
                straight_num2=0;
                return;
            }
        }        
    }

    n-=special_cnt;

    for(int i=0;i<5;i++)
    {
        for(int j=i+1;j<5;j++)
        {
            if(st[i]<st[j])
            {
                int temp=st[i];
                st[i]=st[j];
                st[j]=temp;
            }
        }
    }

    for(int i=n;i<5;i++)
    {
        if(st[i]==special_card)st[i]=15;
        if(st[i]==1)st[i]=14;
    }

    for(int i=n;i<5;i++)
    {
        for(int j=i+1;j<5;j++)
        {
            if(st[i]<st[j])
            {
                int temp=st[i];
                st[i]=st[j];
                st[j]=temp;
            }
        }
    }

    for(int i=0,k=0;i<27;i++)
    {
        if((n>0&&cardarray[play_round-1][i].value==15&&cardarray[play_round-1][i].color==3)||(n<=0&&cardarray[play_round-1][i].value==st[k]&&cardarray[play_round-1][i].color==color))
        {
            n--;k++;
            card[i]->click();
            if(k==5)break;
        }
    }
}




void CardsWindow::on_card_01_clicked()
{
    if(ui->card_01->isChecked())
    {
        int xx=ui->card_01->x();
        int yy=ui->card_01->y()-30;
        ui->card_01->move(xx,yy);
    }
    else
    {
        int xx=ui->card_01->x();
        int yy=ui->card_01->y()+30;
        ui->card_01->move(xx,yy);
    }
}

void CardsWindow::on_card_02_clicked()
{
    if(ui->card_02->isChecked())
    {
        int xx=ui->card_02->x();
        int yy=ui->card_02->y()-30;
        ui->card_02->move(xx,yy);
    }
    else
    {
        int xx=ui->card_02->x();
        int yy=ui->card_02->y()+30;
        ui->card_02->move(xx,yy);
    }
}

void CardsWindow::on_card_03_clicked()
{
    if(ui->card_03->isChecked())
    {
        int xx=ui->card_03->x();
        int yy=ui->card_03->y()-30;
        ui->card_03->move(xx,yy);
    }
    else
    {
        int xx=ui->card_03->x();
        int yy=ui->card_03->y()+30;
        ui->card_03->move(xx,yy);
    }
}

void CardsWindow::on_card_04_clicked()
{
    if(ui->card_04->isChecked())
    {
        int xx=ui->card_04->x();
        int yy=ui->card_04->y()-30;
        ui->card_04->move(xx,yy);
    }
    else
    {
        int xx=ui->card_04->x();
        int yy=ui->card_04->y()+30;
        ui->card_04->move(xx,yy);
    }
}

void CardsWindow::on_card_05_clicked()
{
    if(ui->card_05->isChecked())
    {
        int xx=ui->card_05->x();
        int yy=ui->card_05->y()-30;
        ui->card_05->move(xx,yy);
    }
    else
    {
        int xx=ui->card_05->x();
        int yy=ui->card_05->y()+30;
        ui->card_05->move(xx,yy);
    }
}

void CardsWindow::on_card_06_clicked()
{
    if(ui->card_06->isChecked())
    {
        int xx=ui->card_06->x();
        int yy=ui->card_06->y()-30;
        ui->card_06->move(xx,yy);
    }
    else
    {
        int xx=ui->card_06->x();
        int yy=ui->card_06->y()+30;
        ui->card_06->move(xx,yy);
    }
}

void CardsWindow::on_card_07_clicked()
{
    if(ui->card_07->isChecked())
    {
        int xx=ui->card_07->x();
        int yy=ui->card_07->y()-30;
        ui->card_07->move(xx,yy);
    }
    else
    {
        int xx=ui->card_07->x();
        int yy=ui->card_07->y()+30;
        ui->card_07->move(xx,yy);
    }
}

void CardsWindow::on_card_08_clicked()
{
    if(ui->card_08->isChecked())
    {
        int xx=ui->card_08->x();
        int yy=ui->card_08->y()-30;
        ui->card_08->move(xx,yy);
    }
    else
    {
        int xx=ui->card_08->x();
        int yy=ui->card_08->y()+30;
        ui->card_08->move(xx,yy);
    }
}

void CardsWindow::on_card_09_clicked()
{
    if(ui->card_09->isChecked())
    {
        int xx=ui->card_09->x();
        int yy=ui->card_09->y()-30;
        ui->card_09->move(xx,yy);
    }
    else
    {
        int xx=ui->card_09->x();
        int yy=ui->card_09->y()+30;
        ui->card_09->move(xx,yy);
    }
}

void CardsWindow::on_card_10_clicked()
{
    if(ui->card_10->isChecked())
    {
        int xx=ui->card_10->x();
        int yy=ui->card_10->y()-30;
        ui->card_10->move(xx,yy);
    }
    else
    {
        int xx=ui->card_10->x();
        int yy=ui->card_10->y()+30;
        ui->card_10->move(xx,yy);
    }
}

void CardsWindow::on_card_11_clicked()
{
    if(ui->card_11->isChecked())
    {
        int xx=ui->card_11->x();
        int yy=ui->card_11->y()-30;
        ui->card_11->move(xx,yy);
    }
    else
    {
        int xx=ui->card_11->x();
        int yy=ui->card_11->y()+30;
        ui->card_11->move(xx,yy);
    }
}

void CardsWindow::on_card_12_clicked()
{
    if(ui->card_12->isChecked())
    {
        int xx=ui->card_12->x();
        int yy=ui->card_12->y()-30;
        ui->card_12->move(xx,yy);
    }
    else
    {
        int xx=ui->card_12->x();
        int yy=ui->card_12->y()+30;
        ui->card_12->move(xx,yy);
    }
}

void CardsWindow::on_card_13_clicked()
{
    if(ui->card_13->isChecked())
    {
        int xx=ui->card_13->x();
        int yy=ui->card_13->y()-30;
        ui->card_13->move(xx,yy);
    }
    else
    {
        int xx=ui->card_13->x();
        int yy=ui->card_13->y()+30;
        ui->card_13->move(xx,yy);
    }
}

void CardsWindow::on_card_14_clicked()
{
    if(ui->card_14->isChecked())
    {
        int xx=ui->card_14->x();
        int yy=ui->card_14->y()-30;
        ui->card_14->move(xx,yy);
    }
    else
    {
        int xx=ui->card_14->x();
        int yy=ui->card_14->y()+30;
        ui->card_14->move(xx,yy);
    }
}

void CardsWindow::on_card_15_clicked()
{
    if(ui->card_15->isChecked())
    {
        int xx=ui->card_15->x();
        int yy=ui->card_15->y()-30;
        ui->card_15->move(xx,yy);
    }
    else
    {
        int xx=ui->card_15->x();
        int yy=ui->card_15->y()+30;
        ui->card_15->move(xx,yy);
    }
}

void CardsWindow::on_card_16_clicked()
{
    if(ui->card_16->isChecked())
    {
        int xx=ui->card_16->x();
        int yy=ui->card_16->y()-30;
        ui->card_16->move(xx,yy);
    }
    else
    {
        int xx=ui->card_16->x();
        int yy=ui->card_16->y()+30;
        ui->card_16->move(xx,yy);
    }
}

void CardsWindow::on_card_17_clicked()
{
    if(ui->card_17->isChecked())
    {
        int xx=ui->card_17->x();
        int yy=ui->card_17->y()-30;
        ui->card_17->move(xx,yy);
    }
    else
    {
        int xx=ui->card_17->x();
        int yy=ui->card_17->y()+30;
        ui->card_17->move(xx,yy);
    }
}

void CardsWindow::on_card_18_clicked()
{
    if(ui->card_18->isChecked())
    {
        int xx=ui->card_18->x();
        int yy=ui->card_18->y()-30;
        ui->card_18->move(xx,yy);
    }
    else
    {
        int xx=ui->card_18->x();
        int yy=ui->card_18->y()+30;
        ui->card_18->move(xx,yy);
    }
}

void CardsWindow::on_card_19_clicked()
{
    if(ui->card_19->isChecked())
    {
        int xx=ui->card_19->x();
        int yy=ui->card_19->y()-30;
        ui->card_19->move(xx,yy);
    }
    else
    {
        int xx=ui->card_19->x();
        int yy=ui->card_19->y()+30;
        ui->card_19->move(xx,yy);
    }
}

void CardsWindow::on_card_20_clicked()
{
    if(ui->card_20->isChecked())
    {
        int xx=ui->card_20->x();
        int yy=ui->card_20->y()-30;
        ui->card_20->move(xx,yy);
    }
    else
    {
        int xx=ui->card_20->x();
        int yy=ui->card_20->y()+30;
        ui->card_20->move(xx,yy);
    }
}

void CardsWindow::on_card_21_clicked()
{
    if(ui->card_21->isChecked())
    {
        int xx=ui->card_21->x();
        int yy=ui->card_21->y()-30;
        ui->card_21->move(xx,yy);
    }
    else
    {
        int xx=ui->card_21->x();
        int yy=ui->card_21->y()+30;
        ui->card_21->move(xx,yy);
    }
}

void CardsWindow::on_card_22_clicked()
{
    if(ui->card_22->isChecked())
    {
        int xx=ui->card_22->x();
        int yy=ui->card_22->y()-30;
        ui->card_22->move(xx,yy);
    }
    else
    {
        int xx=ui->card_22->x();
        int yy=ui->card_22->y()+30;
        ui->card_22->move(xx,yy);
    }
}

void CardsWindow::on_card_23_clicked()
{
    if(ui->card_23->isChecked())
    {
        int xx=ui->card_23->x();
        int yy=ui->card_23->y()-30;
        ui->card_23->move(xx,yy);
    }
    else
    {
        int xx=ui->card_23->x();
        int yy=ui->card_23->y()+30;
        ui->card_23->move(xx,yy);
    }
}

void CardsWindow::on_card_24_clicked()
{
    if(ui->card_24->isChecked())
    {
        int xx=ui->card_24->x();
        int yy=ui->card_24->y()-30;
        ui->card_24->move(xx,yy);
    }
    else
    {
        int xx=ui->card_24->x();
        int yy=ui->card_24->y()+30;
        ui->card_24->move(xx,yy);
    }
}

void CardsWindow::on_card_25_clicked()
{
    if(ui->card_25->isChecked())
    {
        int xx=ui->card_25->x();
        int yy=ui->card_25->y()-30;
        ui->card_25->move(xx,yy);
    }
    else
    {
        int xx=ui->card_25->x();
        int yy=ui->card_25->y()+30;
        ui->card_25->move(xx,yy);
    }
}

void CardsWindow::on_card_26_clicked()
{
    if(ui->card_26->isChecked())
    {
        int xx=ui->card_26->x();
        int yy=ui->card_26->y()-30;
        ui->card_26->move(xx,yy);
    }
    else
    {
        int xx=ui->card_26->x();
        int yy=ui->card_26->y()+30;
        ui->card_26->move(xx,yy);
    }
}

void CardsWindow::on_card_27_clicked()
{
    if(ui->card_27->isChecked())
    {
        int xx=ui->card_27->x();
        int yy=ui->card_27->y()-30;
        ui->card_27->move(xx,yy);
    }
    else
    {
        int xx=ui->card_27->x();
        int yy=ui->card_27->y()+30;
        ui->card_27->move(xx,yy);
    }
}
