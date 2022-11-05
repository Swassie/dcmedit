#pragma once
#include "common/Callback_ref.h"
#include "common/Event_exceptions.h"
#include "common/IEvent.h"
#include "common/Scoped_disable.h"
#include "logging/Log.h"

#include <algorithm>
#include <functional>
#include <limits>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>

template<class ... Parameters>
class Event : public IEvent
{
public:
    using Callback = std::function<void(Parameters...)>;

    Event()
        : m_enabled(true),
          m_deferred(false),
          m_latest_id_used(0),
          m_callback_removed(false) {}

    void enable_event(bool enable) override {
        m_enabled = enable;
        m_deferred = false;
    }

    bool enabled() const override {
        return m_enabled;
    }

    bool deferred() const override {
        return m_deferred;
    }

    Callback_ref add_callback(const Callback& callback) {
        const Id id = get_available_id();
        m_callbacks.emplace(id, callback);
        m_callback_order.push_back(id);

        return Callback_ref([this, id] {remove_callback(id);});
    }

    void operator()(Parameters... parameters) {
        if(!m_enabled) {
            m_deferred = true;
            return;
        }
        Scoped_disable disable(*this);
        m_called_callbacks.clear();

        for(size_t i = 0; i < m_callback_order.size(); i++) {
            const Id callback_id = m_callback_order[i];

            if(m_called_callbacks.count(callback_id) != 0) {
                continue;
            }
            m_called_callbacks.insert(callback_id);
            m_callback_removed = false;

            /* Call a copy of the callback, since the one in the map
             * might be removed during callback. */
            const Callback callback = m_callbacks[callback_id];
            callback(parameters...);

            if(m_callback_removed) {
                /* If a callback is removed during callback, iterate from the start. */
                i = (std::numeric_limits<decltype(i)>::max)();
            }
        }
    }

private:
    using Id = uint16_t;

    void remove_callback(const Id id) {
        /* An added callback might get the same ID as a deleted, already called callback.
         * Without this the added callback wouldn't be called during the same event. */
        m_called_callbacks.erase(id);
        m_callbacks.erase(id);

        auto it = std::find_if(m_callback_order.begin(), m_callback_order.end(), [id] (const Id id_) {
            return id_ == id;
        });
        if(it != m_callback_order.end()) {
            m_callback_order.erase(it);
            m_callback_removed = true;
        }
        else {
            Log::debug("Could not find callback to remove.");
        }
    }

    Id get_available_id() {
        const Id first_candidate = m_latest_id_used + 1;
        Id candidate = first_candidate;
        do {
            if(m_callbacks.count(candidate) == 0) {
                m_latest_id_used = candidate;
                return candidate;
            }
            candidate++;
        } while(candidate != first_candidate);

        throw Event_error("No more capacity for event callbacks.");
    }

    bool m_enabled;
    bool m_deferred;
    Id m_latest_id_used;
    std::unordered_map<Id, Callback> m_callbacks;
    std::vector<Id> m_callback_order;
    std::unordered_set<Id> m_called_callbacks;
    bool m_callback_removed;
};
