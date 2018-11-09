#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QLineEdit>
#include <QIntValidator>
#include <QSoundEffect>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QUrl>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:

    void on_controlButton_clicked();
    void on_countdown_timeout();
    void on_reminder_timeout();
    void get_Min_Sec(int *min, int *sec);
    void set_Min_Sec(int min, int sec);
    void windows_reset();

    void on_preset01_clicked();
    void on_preset02_clicked();
    void on_preset03_clicked();
    void on_preset05_clicked();
    void on_preset10_clicked();
    void on_preset15_clicked();
    void on_preset20_clicked();

private:
    Ui::Dialog *ui;
    QTimer *timer;
    QIntValidator *intValidator, *intValidator2;
    QLineEdit* textMin, *textSec;
    QPushButton* button;
    int colorIdx;
    QColor initialBackgroundColor, initialButtonColor;
    QSoundEffect *soundPlayer;
};

#endif // DIALOG_H
