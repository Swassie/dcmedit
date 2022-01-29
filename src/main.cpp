#include "Version.h"
#include "dcmedit.h"
#include "logging/Console_logger.h"
#include "logging/Log.h"

#include <string>

int main(int argc, char** argv) {
    Log log(Log_level::info);
    log.add_logger(std::make_unique<Console_logger>());

    Log::info("dcmedit " + std::string(dcmedit_version));

    dcmedit dcmedit;
    int exit_code = dcmedit.run(argc, argv);
    return exit_code;
}
