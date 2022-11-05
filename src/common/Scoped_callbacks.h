#pragma once
#include "common/Callback_ref.h"

#include <vector>

/* Helps manage the lifetime of callbacks. Removes them when this object is destroyed. */
class Scoped_callbacks
{
public:
    ~Scoped_callbacks();

    void add_to_scope(const Callback_ref&);
    void remove_callbacks();

private:
    std::vector<Callback_ref> m_callbacks;
};
