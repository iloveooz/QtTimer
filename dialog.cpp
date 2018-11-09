#include "dialog.h"
#include "ui_dialog.h"
#include <QtDebug>
#include <QFile>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);

    intValidator = new QIntValidator(0, 59, this);
    intValidator2 = new QIntValidator(0, 999, this);
    textMin = this->findChild<QLineEdit *>("textMin");
    textSec = this->findChild<QLineEdit *>("textSec");
    textMin->setValidator(intValidator2);
    textSec->setValidator(intValidator);

    button = this->findChild<QPushButton *>("controlButton");

    timer = new QTimer(this);
    timer->setTimerType(Qt::PreciseTimer);

    colorIdx = 0;

    initialBackgroundColor = this->palette().color(QPalette::Window).toRgb();

    soundPlayer = new QSoundEffect(this);
    soundPlayer->setSource(QUrl(QStringLiteral("qrc:/sound/alarm.wav")));
    soundPlayer->setLoopCount(3);
    this->setFixedSize(this->width(),this->height());

    connect(textMin, SIGNAL(returnPressed()), this, SIGNAL(on_controlButton_clicked()));
    connect(textSec, SIGNAL(returnPressed()), this, SIGNAL(on_controlButton_clicked()));
}

Dialog::~Dialog()
{
    delete soundPlayer;
    delete intValidator;
    delete intValidator2;
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
    button->setStyleSheet("color: green");

    this->setWindowTitle("Timer");
    textMin->setEnabled(true);
    textSec->setEnabled(true);
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
        soundPlayer->play();
        button->setStyleSheet("color: #000099");
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
        button->setStyleSheet("color: #FF0099");
        connect(timer, SIGNAL(timeout()), this, SLOT(on_countdown_timeout()));
        timer->start(1000);
        textMin->setEnabled(false);
        textSec->setEnabled(false);
    } else if (!buttonStr.compare("Stop") || !buttonStr.compare("Reset")){
        timer->stop();
        disconnect(timer, SIGNAL(timeout()), 0, 0);        
        this->windows_reset();
        if (!buttonStr.compare("Reset")){
            soundPlayer->stop();
        }
    }
}

void Dialog::on_preset01_clicked()
{
    textMin->setText("01");
    textSec->setText("00");
}

void Dialog::on_preset02_clicked()
{
    textMin->setText("02");
    textSec->setText("00");
}

void Dialog::on_preset03_clicked()
{
    textMin->setText("03");
    textSec->setText("00");
}

void Dialog::on_preset05_clicked()
{
    textMin->setText("05");
    textSec->setText("00");
}

void Dialog::on_preset10_clicked()
{
    textMin->setText("10");
    textSec->setText("00");
}

void Dialog::on_preset15_clicked()
{
    textMin->setText("15");
    textSec->setText("00");
}

void Dialog::on_preset20_clicked()
{
    textMin->setText("20");
    textSec->setText("00");
}
