#ifndef GLOBAL_CUSTOMEVENTLOOP_DEFINE_H
#define GLOBAL_CUSTOMEVENTLOOP_DEFINE_H

#include <QString>

class CustomEventLoop;

// 事件循环类型
enum EventLoopType
{
    EventLoop4Default = -1,
    EventLoop4Other = 1000,
};

// 事件循环消息
struct EventLoopInfo
{
    QString id; // 唯一ID
    int iEventLoopType; // 事件循环ID

    // 构造
    EventLoopInfo() :
    id(""),
    iEventLoopType(EventLoop4Default)
    {
    }
};

// 事件循环单元
struct EventLoopUnit
{
    CustomEventLoop *eventLoop; // 事件循环
    EventLoopInfo eventLoopInfo; // 事件循环信息

    // 构造
    EventLoopUnit() :
        eventLoop(0)
    {
    }
};

#endif // GLOBAL_CUSTOMEVENTLOOP_DEFINE_H
