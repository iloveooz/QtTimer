#include "dialog.h"
#include "ui_dialog.h"
#include <QtDebug>
#include <QLineEdit>
#include <QIntValidator>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    intValidator = new QIntValidator(0, 99, this);
    textMin = this->findChild<QLineEdit *>("textMin");
    textSec = this->findChild<QLineEdit *>("textSec");
    textMin->setValidator(intValidator);
    textSec->setValidator(intValidator);

    button = this->findChild<QPushButton *>("controlButton");
    timer = new QTimer(this);
    colorIdx = 0;

    initialBackgroundColor = this->palette().color(QPalette::Background).toRgb();
}

Dialog::~Dialog()
{
    delete intValidator;
    delete timer;
    delete ui;
}

void Dialog::get_Min_Sec(int *min, int *sec){
    int minutes = textMin->text().toInt();
    int seconds = textSec->text().toInt();
    int secTotal = minutes * 60 + seconds;
    *min = secTotal / 60;
    *sec = secTotal % 60;
}

void Dialog::set_Min_Sec(int min, int sec){
    QString minStr = "";
    QString secStr = "";
    if (min < 10){
        minStr += "0";
    }
    minStr += QString::number(min);
    if (sec < 10) {
        secStr += "0";
    }
    secStr += QString::number(sec);
    textMin->setText(minStr);
    textSec->setText(secStr);
}

void Dialog::windows_reset(){
    QPalette pal = this->palette();
    pal.setColor(QPalette::Window, initialBackgroundColor);

    this->setPalette(pal);
    button->setText("Start");
    this->setWindowTitle("Timer");
}

void Dialog::on_reminder_timeout(){
    QPalette pal = this->palette();
    switch(colorIdx){
        case 0:
            pal.setColor(QPalette::Window, Qt::yellow);
            break;
        case 1:
            pal.setColor(QPalette::Window, Qt::red);
            break;
    }
    colorIdx ++;
    colorIdx %= 2;
    this->setPalette(pal);
    if (colorIdx % 2) {
        this->setWindowTitle("Time up!!!");
    } else {
        this->setWindowTitle("Now!!!");
    }
}

void Dialog::on_countdown_timeout(){
    int minutes, seconds, secTotal;
    this->get_Min_Sec(&minutes, &seconds);
    secTotal = minutes * 60 + seconds;
    if (secTotal > 0){
        secTotal --;
        minutes = secTotal / 60;
        seconds = secTotal % 60;
        this->set_Min_Sec(minutes, seconds);
    }
    if (secTotal == 0) {
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), 0, 0);
        button->setText("Reset");
        connect(timer, SIGNAL(timeout()), this, SLOT(on_reminder_timeout()));
        timer->start(200);        
    }
}

void Dialog::on_controlButton_clicked()
{
    QString buttonStr = button->text();
    if (!buttonStr.compare("Start")){
        int minutes, seconds;
        this->get_Min_Sec(&minutes, &seconds);
        this->set_Min_Sec(minutes, seconds);
        button->setText("Stop");
        connect(timer, SIGNAL(timeout()), this, SLOT(on_countdown_timeout()));
        timer->start(1000);
    } else if (!buttonStr.compare("Stop") || !buttonStr.compare("Reset")){
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), 0, 0);        
        this->windows_reset();
    }
}