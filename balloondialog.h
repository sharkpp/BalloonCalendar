#ifndef BALLOONDIALOG_H
#define BALLOONDIALOG_H

#include <QObject>
#include <QDialog>

class QTimer;

class BalloonDialog
        : public QDialog
{
    Q_OBJECT

public:
    BalloonDialog(QWidget *parent = 0);

protected:
    void resizeEvent(QResizeEvent *);
    void focusOutEvent(QFocusEvent *event);
    void showEvent(QShowEvent *event);
    bool event(QEvent *e);

private slots:
    void on_lazyShowWindow();

private:
    QTimer *lazyShowWindow;
};

#endif // BALLOONDIALOG_H
