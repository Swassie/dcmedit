#pragma once
#include "logging/Log.h"

#include <functional>
#include <limits>

template<class ... Parameters>
class Event
{
public:
    using Id = int;
    using Handler = std::function<void(Parameters...)>;
    using Handler_remover = std::function<void()>;

    Event()
        : m_defer_event(false),
          m_deferred(false),
          m_next_handler_id(0) {}

    void defer_event(bool defer_event) {
        m_defer_event = defer_event;
    }

    bool deferred() const {
        return m_deferred;
    }

    Handler_remover operator+=(const Handler& handler) {
        const Id id = m_next_handler_id++;
        m_handlers.push_back({id, handler});

        return [this, id] {remove_handler(id);};
    }

    void remove_handler(const Id id) {
        for(auto it = m_handlers.begin(); it != m_handlers.end(); ++it) {
            if(it->id == id) {
                m_handlers.erase(it);
                return;
            }
        }
        Log::debug("Could not find handler for removal.");
    }

    void operator()(Parameters... parameters) {
        if(m_defer_event) {
            m_deferred = true;
            return;
        }
        m_deferred = false;

        /* Since each handler can add/remove handlers, we must iterate
         * from the start of the vector after calling each handler. */
        Id previous_handler_id = -1;
        for(size_t i = 0; i < m_handlers.size(); i++) {
            if(m_handlers[i].id <= previous_handler_id) {
                continue;
            }
            previous_handler_id = m_handlers[i].id;

            /* Call a copy of the handler, since the one in the vector
             * might be deleted due to removal or vector reallocation. */
            const Handler handler = m_handlers[i].handler;
            handler(parameters...);
            i = (std::numeric_limits<decltype(i)>::max)();
        }
    }

protected:
    struct Handler_pair {Id id; Handler handler;};

    bool m_defer_event;
    bool m_deferred;
    Id m_next_handler_id;
    std::vector<Handler_pair> m_handlers;
};
