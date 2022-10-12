#include "Dcmedit.h"
#include "common/App_info.h"
#include "logging/Console_logger.h"
#include "logging/Log.h"
#include "ui/View_factory.h"

#include <QApplication>
#include <string>

int main(int argc, char** argv) {
    Log log(Log_level::info);
    log.add_logger(std::make_unique<Console_logger>());

    Log::info("dcmedit " + std::string(App_info::version));

    QApplication app(argc, argv);

    View_factory view_factory;
    Dcmedit dcmedit(view_factory);

    return app.exec();
}
