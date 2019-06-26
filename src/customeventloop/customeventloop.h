#ifndef CUSTOMEVENTLOOP_H
#define CUSTOMEVENTLOOP_H

#include <QObject>
#include <QTimer>
#include <QEventLoop>

class CustomEventLoop : public QObject
{
    Q_OBJECT
public:
    explicit CustomEventLoop(QObject *parent = 0);

    // 开启事件循环
    void startEventLoop(int iTimeout);

    // 停止事件循环
    void stopEventLoop();

signals:
    void sigFinished();
    void sigTimeout();

private slots:
    void onTimeout(); // 超时

private:
    QTimer m_timer4timeout; // 用于超时处理
    QEventLoop m_eventLoop; // 事件循环
};

#endif // CUSTOMEVENTLOOP_H
