#include "customeventloop.h"


CustomEventLoop::CustomEventLoop(QObject *parent) :
    QObject(parent)
{
    connect(&m_timer4timeout, SIGNAL(timeout()), this, SLOT(onTimeout()));
}

void CustomEventLoop::startEventLoop(int iTimeout)
{
    if (m_eventLoop.isRunning())
        m_eventLoop.exit();

    if (iTimeout > 0)
    {
        if (m_timer4timeout.isActive())
            m_timer4timeout.stop();

        m_timer4timeout.setInterval(iTimeout);
        m_timer4timeout.start();
    }

    m_eventLoop.exec();
}

void CustomEventLoop::stopEventLoop()
{
    if (m_timer4timeout.isActive())
        m_timer4timeout.stop();

    if (m_eventLoop.isRunning())
        m_eventLoop.exit();

    emit sigFinished();
}

void CustomEventLoop::onTimeout()
{
    if (m_timer4timeout.isActive())
        m_timer4timeout.stop();

    if (m_eventLoop.isRunning())
        m_eventLoop.exit();

    emit sigTimeout();
}
