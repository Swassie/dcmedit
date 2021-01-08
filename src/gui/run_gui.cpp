#include "gui/run_gui.h"

#include "gui/Main_window.h"

#include <QApplication>

int run_gui(int argc, char** argv) {
    QApplication app(argc, argv);
    app.setApplicationName("dcmedit");

    Main_window main_window;
    main_window.setup_start_studio();
    main_window.show();

    return app.exec();
}
