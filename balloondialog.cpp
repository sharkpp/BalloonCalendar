#include "balloondialog.h"
#include <QBitmap>
#include <QPainter>
#include <QRegularExpression>
#include <QEvent>
#include <QTimer>
#include <QDebug>
#include <QApplication>
#include "focuser.h"

BalloonDialog::BalloonDialog(QWidget *parent)
    : QDialog(parent)
    , lazyShowWindow(new QTimer(this))
{
    qDebug() << "BalloonDialog::BalloonDialog()";

    connect(lazyShowWindow, SIGNAL(timeout()), this, SLOT(on_lazyShowWindow()));

    setModal(true);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);
}

void BalloonDialog::resizeEvent(QResizeEvent *)
{
    QRect wndRect = rect();

    // *__/\___  * = 原点
    // |      |  時計回りに描画
    // +------+

    const int FUKIDASHI_HEIGHT = 15;
    const int FUKIDASHI_WIDTH  = 30;

    // 吹き出しの矢印分をずらす
    QString ss = styleSheet();
    ss.replace(QRegularExpression("\\s*margin-top\\s*:\\s*.+?;"), "");
    setStyleSheet(QString("%1 margin-top: %2px;").arg(ss).arg(FUKIDASHI_HEIGHT));

    // 吹き出しの形にウインドウの形を加工
    QPolygon poly;
    poly  << QPoint(wndRect.x(), wndRect.y() + FUKIDASHI_HEIGHT)
          << QPoint(wndRect.x() + wndRect.width() / 2 - FUKIDASHI_WIDTH / 2, wndRect.y() + FUKIDASHI_HEIGHT)
          << QPoint(wndRect.x() + wndRect.width() / 2, wndRect.y())
          << QPoint(wndRect.x() + wndRect.width() / 2 + FUKIDASHI_WIDTH / 2, wndRect.y() + FUKIDASHI_HEIGHT)
          << QPoint(wndRect.x() + wndRect.width(), wndRect.y() + FUKIDASHI_HEIGHT)
          << QPoint(wndRect.x() + wndRect.width(), wndRect.y() + wndRect.height())
          << QPoint(wndRect.x(), wndRect.y() + wndRect.height())
          //<< QPoint(wndRect.x(), wndRect.y() + FUKIDASHI_HEIGHT)
             ;
    QRegion newMask(poly);
    setMask(newMask);
}

bool BalloonDialog::event(QEvent *e)
{
//    qDebug() << "BalloonDialog::event" << e->type();
    qDebug() << "BalloonDialog::event" << e->type() << QApplication::activeWindow() << (QApplication::activeWindow() == this ? "AM" : "AM NOT");
    if (QEvent::WindowDeactivate == e->type()) {
        qDebug() << "BalloonDialog::event" << __LINE__;
        done(0);
        e->ignore();
        return true;
    }
    return QDialog::event(e) ;
}

void BalloonDialog::focusOutEvent(QFocusEvent *event)
{
    qDebug() << "BalloonDialog::focusOutEvent";
    //done(0);
}

void BalloonDialog::showEvent(QShowEvent *event)
{
    qDebug() << "BalloonDialog::showEvent";
    //activateWindow();
    //setFocus();
    //lazyShowWindow->start(10000);
    Focuser f(this);
    f.focus();
}

void BalloonDialog::on_lazyShowWindow()
{
    activateWindow();
    setFocus();

}

