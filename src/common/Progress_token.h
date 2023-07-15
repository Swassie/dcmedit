#pragma once

class Progress_token
{
public:
    virtual ~Progress_token() = default;

    virtual void set_max_progress(int) = 0;
    virtual void increment_progress() = 0;
    virtual bool cancelled() const = 0;
};
