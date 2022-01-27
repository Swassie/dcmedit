#pragma once
#include <functional>
#include <vector>

/* Helps manage the lifetime of event handlers,
 * regardless of the Event template specialization. */
class Scoped_event_handlers
{
public:
    using Handler_remover = std::function<void()>;

    ~Scoped_event_handlers();

    void operator+=(const Handler_remover&);
    void remove_all();

protected:
    std::vector<Handler_remover> m_handler_removers;
};
