#ifndef CALENDARPOPUP_H
#define CALENDARPOPUP_H

#include "popover.h"

namespace Ui {
class CalendarPopup;
}

class CalendarPopup
        : public Popover
{
    Q_OBJECT

public:
    explicit CalendarPopup(QWidget *parent = 0);
    ~CalendarPopup();

private slots:
    void on_exitButton_clicked();

private:
    Ui::CalendarPopup *ui;
};

#endif // CALENDARPOPUP_H
