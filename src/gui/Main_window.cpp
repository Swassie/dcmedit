#include "Main_window.h"
#include "View_area.h"

Main_window::Main_window() {
    setCentralWidget(new View_area);
}
