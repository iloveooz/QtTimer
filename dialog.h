#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QTimer>
#include <QLineEdit>
#include <QIntValidator>

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

private:
    Ui::Dialog *ui;
    QTimer *timer;
    QIntValidator *intValidator;
    QLineEdit* textMin, *textSec;
    QPushButton* button;
    int colorIdx;
    QColor initialBackgroundColor;
};

#endif // DIALOG_H
