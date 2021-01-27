#pragma once
#include <QMenu>

class Dicom_studio;
class Main_window;
class Studio;
class View;
class View_factory;
class View_manager;

class Menu : public QMenu
{
    Q_OBJECT
public:
    Menu(QWidget* parent = nullptr);

    // File menu.
    void set_title_file();
    void add_open_files(Studio&);
    void add_save_file(Dicom_studio&);
    void add_save_file_as(Dicom_studio&);
    void add_quit(Main_window&);

    // View menu.
    void set_title_view();
    void add_view_counts(View_manager&);

    // Help menu.
    void set_title_help();
    void add_about(Main_window&);

    // View context menu.
    void add_switch_to_image_view(View&, View_factory&, View_manager&);
    void add_switch_to_dataset_view(View&, View_factory&, View_manager&);
};
