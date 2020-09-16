#pragma once

class Main_window;
class QMenu;
class QMenuBar;
class Workspace_view;

namespace Common_actions
{
    enum class Studio {
        dicom,
        test
    };

    QMenu* add_file_menu(QMenuBar&);
    QMenu* add_view_menu(QMenuBar&);
    QMenu* add_studio_menu(QMenuBar&);
    void add_open_file(QMenu&, Main_window&);
    void add_view_counts(QMenu&, Workspace_view&);
    void add_studios(QMenu&, Main_window&, Studio);
}
