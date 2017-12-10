#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calendarpopup.h"
#include <QSystemTrayIcon>
#include <QShowEvent>
#include <QDesktopWidget>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
    , calendar(nullptr)
{
    hide();
    setFocusPolicy(Qt::StrongFocus);
    //ui->setupUi(this);

    trayIcon = new QSystemTrayIcon(this);
    //trayIcon->setContextMenu(trayIconMenu);

    QIcon icon = QApplication::style()->standardIcon( QStyle::SP_TitleBarMenuButton );
    trayIcon->setIcon(icon);

    connect(trayIcon, &QSystemTrayIcon::messageClicked, this, &MainWindow::onTrayMessageClicked);
    connect(trayIcon, &QSystemTrayIcon::activated,      this, &MainWindow::onTrayIconActivated);

    trayIcon->show();

}

MainWindow::~MainWindow()
{
    delete calendar;
    //delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
#ifdef Q_OS_OSX
    if (!event->spontaneous() || !isVisible()) {
        return;
    }
#endif
    event->ignore();
}

void MainWindow::showEvent(QShowEvent *event)
{
    //event->ignore();
}

void MainWindow::on_pushButton_clicked()
{
    //QRect rc = ui->pushButton->rect();
    //CalendarPopup dlg;
    //dlg.exec();

}

void MainWindow::onTrayIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    qDebug() << "MainWindow::onTrayIconActivated" << reason << calendar;
    switch (reason) {
    case QSystemTrayIcon::Trigger: {
        qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << calendar;
        if (!calendar) {
            qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << calendar;
            calendar = new CalendarPopup();
            QRect rcTray = trayIcon->geometry();
            QRect rc = calendar->geometry();
            qDebug() << rcTray << rc;
            rc.setRect(rcTray.left() - (rc.width()-rcTray.width())/2, rcTray.bottom(), rc.width(), rc.height());
            calendar->setGeometry(rc);
            calendar->exec();
            qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << calendar;
        }
        else {
            qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << calendar;
            calendar->close();
            qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << calendar;
        }
        qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << calendar;
        delete calendar;
        calendar = nullptr;
        qDebug() << "MainWindow::onTrayIconActivated" << __LINE__ << calendar;
        break; }
    case QSystemTrayIcon::DoubleClick:
        //iconComboBox->setCurrentIndex((iconComboBox->currentIndex() + 1) % iconComboBox->count());
        break;
    case QSystemTrayIcon::MiddleClick:
        break;
    default:
        ;
    }
}

void MainWindow::onTrayMessageClicked()
{

}


void MainWindow::focusInEvent(QFocusEvent *event)
{
    qDebug() << "MainWindow::focusInEvent";

}

bool MainWindow::event(QEvent *e)
{
    qDebug() << e->type() << qApp->activeWindow() << (qApp->activeWindow() == this ? "AM" : "AM NOT");
    switch ( e->type() )
    {
    case QEvent::WindowActivate:
        qDebug( "WindowActivate - I %s the active window!", qApp->activeWindow() == this ? "AM" : "AM NOT" );
        break;
    }
    return QMainWindow::event(e) ;
}
