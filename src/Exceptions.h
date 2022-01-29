#pragma once
#include <stdexcept>
#include <string>

class DcmeditException : public std::runtime_error
{
public:
    DcmeditException(const std::string&);
};

class TagPathNotFoundException : public DcmeditException
{
public:
    TagPathNotFoundException(const std::string&);
};
