#include "eventloopmanager.h"
#include "customeventloop.h"
#include <QUuid>

// 单实例
EventLoopManager *EventLoopManager::m_instance = 0;

EventLoopManager::EventLoopManager(QObject *parent) :
    QObject(parent),
    m_sigMapper4Finish(0),
    m_sigMapper4Timeout(0)
{
    m_sigMapper4Finish = new QSignalMapper(this);
    m_sigMapper4Timeout = new QSignalMapper(this);

    connect(m_sigMapper4Finish, SIGNAL(mapped(QString)),
            this, SLOT(onEventLoopFinished(QString)));
    connect(m_sigMapper4Timeout, SIGNAL(mapped(QString)),
            this, SLOT(onEventLoopTimeout(QString)));
}

EventLoopManager::~EventLoopManager()
{

}

EventLoopManager *EventLoopManager::instance()
{
    if (0 == EventLoopManager::m_instance)
        EventLoopManager::m_instance = new EventLoopManager();

    return EventLoopManager::m_instance;
}

bool EventLoopManager::addEventLoop(QString &id, int iEventLoopType)
{
    // 自定义事件循环ID
    if (EventLoop4Default != iEventLoopType)
    {
        QHash<QString,EventLoopUnit>::iterator itor = m_hashEventLoops.begin();
        while (itor != m_hashEventLoops.end())
        {
            //  已经存在该类型的事件循环
            if (iEventLoopType == itor.value().eventLoopInfo.iEventLoopType)
                return false;
            ++itor;
        }
    }

    // 创建事件循环
    EventLoopUnit tmpUnit;
    tmpUnit.eventLoopInfo.id = QUuid::createUuid().toString();
    // 去掉首尾的“{”和“}”
    if (tmpUnit.eventLoopInfo.id.length() >= 2)
        tmpUnit.eventLoopInfo.id = tmpUnit.eventLoopInfo.id.mid(1, tmpUnit.eventLoopInfo.id.length()-2);
    if (tmpUnit.eventLoopInfo.id.length() <= 0 || m_hashEventLoops.contains(tmpUnit.eventLoopInfo.id))
        return false;

    tmpUnit.eventLoopInfo.iEventLoopType = iEventLoopType;

    tmpUnit.eventLoop = new CustomEventLoop();
    QObject::connect(tmpUnit.eventLoop, SIGNAL(sigFinished()), m_sigMapper4Finish, SLOT(map()));
    QObject::connect(tmpUnit.eventLoop, SIGNAL(sigTimeout()), m_sigMapper4Timeout, SLOT(map()));
    m_sigMapper4Finish->setMapping(tmpUnit.eventLoop, tmpUnit.eventLoopInfo.id);
    m_sigMapper4Timeout->setMapping(tmpUnit.eventLoop, tmpUnit.eventLoopInfo.id);

    id = tmpUnit.eventLoopInfo.id;
    m_hashEventLoops.insert(id, tmpUnit);

    return true;
}

bool EventLoopManager::startEventLoop(const QString &id, int iTimeout)
{
    if (id.length() > 0 && m_hashEventLoops.contains(id))
    {
        m_hashEventLoops[id].eventLoop->startEventLoop(iTimeout);
        return true;
    }

    return false;
}

void EventLoopManager::stopEventLoop(const QString &id)
{
    if (id.length() > 0 && m_hashEventLoops.contains(id))
        m_hashEventLoops[id].eventLoop->stopEventLoop();
}

void EventLoopManager::stopEventLoop(int iEventLoopType)
{
    QHash<QString,EventLoopUnit>::iterator itor = m_hashEventLoops.begin();
    while (itor != m_hashEventLoops.end())
    {
        if (iEventLoopType == itor.value().eventLoopInfo.iEventLoopType)
        {
            itor.value().eventLoop->stopEventLoop();
        }

        ++itor;
    }
}

void EventLoopManager::onEventLoopFinished(const QString &id)
{
    if (id.length() > 0 && m_hashEventLoops.contains(id))
    {
        m_hashEventLoops[id].eventLoop->deleteLater();
        m_hashEventLoops.remove(id);

        emit sigEventLoopFinished(id);
    }
}

void EventLoopManager::onEventLoopTimeout(const QString &id)
{
    if (id.length() > 0 && m_hashEventLoops.contains(id))
    {
        m_hashEventLoops[id].eventLoop->deleteLater();
        m_hashEventLoops.remove(id);

        emit sigEventLoopTimeout(id);
    }
}
