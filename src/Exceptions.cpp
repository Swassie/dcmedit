#include "Exceptions.h"

DcmeditException::DcmeditException(const std::string& what)
    : std::runtime_error(what) {}

TagPathNotFoundException::TagPathNotFoundException(const std::string& what)
    : DcmeditException(what) {}
