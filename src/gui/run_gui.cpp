#include "run_gui.h"
#include <QApplication>
#include "Main_window.h"

int run_gui(int argc, char** argv) {
    QApplication app(argc, argv);

    Main_window main_window;
    main_window.show();

    return app.exec();
}
