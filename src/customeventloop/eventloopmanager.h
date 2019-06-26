#ifndef EVENTLOOPMANAGER_H
#define EVENTLOOPMANAGER_H

#include <QObject>
#include <QList>
#include <QHash>
#include <QSignalMapper>
#include "global_customeventloop_define.h"

class EventLoopManager : public QObject
{
    Q_OBJECT
protected:
    explicit EventLoopManager(QObject *parent = 0);

public:
    ~EventLoopManager();

    // 获取单实例接口
    static EventLoopManager *instance();

    // 增加事件循环
    bool addEventLoop(QString& id, int iEventLoopType = EventLoop4Default);

    // 开启事件循环
    bool startEventLoop(const QString& id, int iTimeout = -1);

    // 停止事件循环
    void stopEventLoop(const QString& id);
    void stopEventLoop(int iEventLoopType);

signals:
    void sigEventLoopFinished(const QString& id);
    void sigEventLoopTimeout(const QString& id);

public slots:

private slots:
    void onEventLoopFinished(const QString& id);
    void onEventLoopTimeout(const QString& id);

private:
    static EventLoopManager* m_instance;

    QHash<QString,EventLoopUnit> m_hashEventLoops; // 保存所有事件循环
    QSignalMapper *m_sigMapper4Finish; //
    QSignalMapper *m_sigMapper4Timeout; //
};

#endif // EVENTLOOPMANAGER_H
