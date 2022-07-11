#pragma once
#include <dcmtk/ofstd/ofcond.h>
#include <optional>
#include <string>

enum class Status_code {
    ok,
    error,
    tag_path_not_found
};

class Status
{
public:
    Status(Status_code);
    Status(const std::string&);
    Status(Status_code, const std::string&);

    bool good() const {return m_code == Status_code::ok;}
    bool bad() const {return m_code != Status_code::ok;}
    std::string text() const {return m_text.value_or("");}
    Status_code code() const {return m_code;}

    static const Status ok;
    static Status from(OFCondition cond) {return cond.good() ? ok : Status(cond.text());}

private:
    Status_code m_code;
    std::optional<std::string> m_text;
};
