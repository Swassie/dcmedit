#include "common/App_info.h"
#include "logging/Console_logger.h"
#include "logging/Log.h"
#include "ui/main_view/Main_presenter.h"
#include "ui/main_view/Main_view.h"

#include <QApplication>
#include <memory>
#include <string>

int main(int argc, char** argv) {
    Log log(Log_level::info);
    log.add_logger(std::make_unique<Console_logger>());

    Log::info("dcmedit " + std::string(App_info::version));

    QApplication app(argc, argv);
    Main_view main_view;
    Main_presenter main_presenter(main_view);
    main_view.show();

    return app.exec();
}
