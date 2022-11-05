#pragma once

class IEvent
{
public:
    virtual ~IEvent() = default;

    virtual void enable_event(bool enable) = 0;
    virtual bool enabled() const = 0;
    virtual bool deferred() const = 0;
};
