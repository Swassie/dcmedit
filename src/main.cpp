#include "dcmedit.h"
#include "logging/Console_logger.h"
#include "logging/Log.h"

int main(int argc, char** argv) {
    Log log(Log_level::info);
    log.add_logger(std::make_unique<Console_logger>());

    dcmedit dcmedit;
    int exit_code = dcmedit.run(argc, argv);
    return exit_code;
}
