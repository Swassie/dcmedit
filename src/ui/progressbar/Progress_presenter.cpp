#include "ui/progressbar/Progress_presenter.h"

#include <thread>

Progress_presenter::Progress_presenter(IProgress_view& view, const std::string& text)
    : m_view(view),
      m_progress(0),
      m_cancelled(false) {
    setup_event_callbacks();
    set_max_progress(0);
    m_view.set_value(m_progress);
    m_view.set_text(text);
}

void Progress_presenter::setup_event_callbacks() {
    m_view.cancel_requested.add_callback([this] {m_cancelled = true;});
}

void Progress_presenter::set_max_progress(int max) {
    m_view.set_max(max);
}

void Progress_presenter::increment_progress() {
    m_view.set_value(++m_progress);
}

bool Progress_presenter::cancelled() const {
    return m_cancelled;
}

void Progress_presenter::execute(const std::function<void()>& thread_func) {
    std::thread thread(thread_func);
    m_view.show();
    thread.join();
}

void Progress_presenter::close() {
    m_view.close();
}
