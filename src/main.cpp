#include "gui/run_gui.h"
#include "logging/Console_logger.h"
#include "logging/Log.h"

int main(int argc, char** argv) {
    Log log(Log_level::debug);
    log.add_logger(std::make_unique<Console_logger>());

    int exit_code = run_gui(argc, argv);
    return exit_code;
}
