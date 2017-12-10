#include "calendarpopup.h"
#include "ui_calendarpopup.h"
#include <QApplication>
#include <QDate>
#include <QDebug>

CalendarPopup::CalendarPopup(QWidget *parent)
    : BalloonDialog(parent)
    , ui(new Ui::CalendarPopup)
{
    ui->setupUi(this);
    adjustSize();

    QDate date = QDate::currentDate();
qDebug() << "CalendarPopup::CalendarPopup" << __LINE__ << date;
    date = date.addDays(-date.day() + 1);
    qDebug() << "CalendarPopup::CalendarPopup" << __LINE__ << date;

    date = date.addMonths(-1);
    qDebug() << "CalendarPopup::CalendarPopup" << __LINE__ << date;
    ui->prevMonthName->setText(QString("%1年%2月").arg(date.year()).arg((date.month())));
    ui->prevMonthCalendar->setCurrentPage(date.year(), date.month());

    date = date.addMonths(1);
    qDebug() << "CalendarPopup::CalendarPopup" << __LINE__ << date;
    ui->curMonthName->setText(QString("%1年%2月").arg(date.year()).arg((date.month())));
    ui->curMonthCalendar->setCurrentPage(date.year(), date.month());

    date = date.addMonths(1);
    qDebug() << "CalendarPopup::CalendarPopup" << __LINE__ << date;
    ui->nextMonthName->setText(QString("%1年%2月").arg(date.year()).arg((date.month())));
    ui->nextMonthCalendar->setCurrentPage(date.year(), date.month());

}

CalendarPopup::~CalendarPopup()
{
    delete ui;
}

void CalendarPopup::on_exitButton_clicked()
{
    QApplication::quit();
}
