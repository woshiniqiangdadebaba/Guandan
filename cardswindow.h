#ifndef CARDSWINDOW_H
#define CARDSWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <QString>
#include <QTimer>

#include "judgecards.h"
#include "onecard.h"
#include "player.h"

#define mid_x 350

namespace Ui {
class CardsWindow;
}

class CardsWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit CardsWindow(QWidget *parent = 0);
    ~CardsWindow();

private:
    Ui::CardsWindow *ui;

private:
    QPushButton *card[27];
    QPushButton *dis[8];
    QLabel *player_name[4];
    QLabel *player_number[4];

    Player player;
    JudgeCards judgecards;

    QList <OneCard> cardarray[4];
    int special_card;
    int play_round;
    int best_player;
    int rank[4],ranker;
    int score1,score2;
    int setcard_cnt,set_x;
    int straight_num1,straight_num2;

    OneCard gong_card,huan_card;

    QList <OneCard> card_before;
    QList <OneCard> card_now;

    QTimer *timer=new QTimer(this);
    int timing;

private:
    QString set_name(int m);

    QString card_color(OneCard m);

private slots:

    void on_start_clicked();

    void on_discard_clicked();

    void on_pass_clicked();



    void on_card_01_clicked();

    void on_card_02_clicked();

    void on_card_03_clicked();

    void on_card_04_clicked();

    void on_card_05_clicked();

    void on_card_06_clicked();

    void on_card_07_clicked();

    void on_card_08_clicked();

    void on_card_09_clicked();

    void on_card_10_clicked();

    void on_card_11_clicked();

    void on_card_12_clicked();

    void on_card_13_clicked();

    void on_card_14_clicked();

    void on_card_15_clicked();

    void on_card_16_clicked();

    void on_card_17_clicked();

    void on_card_18_clicked();

    void on_card_19_clicked();

    void on_card_20_clicked();

    void on_card_21_clicked();

    void on_card_22_clicked();

    void on_card_23_clicked();

    void on_card_24_clicked();

    void on_card_25_clicked();

    void on_card_26_clicked();

    void on_card_27_clicked();



    void on_setcard_clicked();

    void on_setbackcard_clicked();

    void on_straight_flush_clicked();

    void on_jingong_clicked();

    void on_huangong_clicked();

    void on_jingong2_clicked();

    void on_huangong2_clicked();


    void timerUpDate();

    void changeplayer();
};

#endif // CARDSWINDOW_H
