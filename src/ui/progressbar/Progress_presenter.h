#pragma once
#include "common/Progress_token.h"
#include "ui/progressbar/IProgress_view.h"

#include <functional>
#include <string>

class Progress_presenter : public Progress_token
{
public:
    Progress_presenter(IProgress_view&, const std::string& text = "");

    /** Set maximum value. 0 gives a busy indicator. */
    void set_max_progress(int) override;
    void increment_progress() override;
    bool cancelled() const override;

    /** Start thread_func in new thread, show progress view and wait for thread. */
    void execute(const std::function<void()>& thread_func);
    void close();

private:
    void setup_event_callbacks();

    IProgress_view& m_view;
    int m_progress;
    bool m_cancelled;
};
