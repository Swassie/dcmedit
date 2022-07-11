#include "common/Status.h"

Status::Status(Status_code code)
    : m_code(code) {}

Status::Status(const std::string& text)
    : m_code(Status_code::error),
      m_text(text) {}

Status::Status(Status_code code, const std::string& text)
    : m_code(code),
      m_text(text) {}

const Status Status::ok = Status(Status_code::ok);
