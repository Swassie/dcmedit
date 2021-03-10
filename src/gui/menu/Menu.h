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
    void add_open_files(Studio&);
    void add_save_file(Dicom_studio&);
    void add_save_file_as(Dicom_studio&);
    void add_save_all_files(Dicom_studio&);
    void add_clear_all_files(Dicom_studio&);
    void add_quit(Main_window&);

    // View menu.
    void add_view_counts(View_manager&);

    // Batch menu.
    void add_batch_element(Dicom_studio&);

    // Help menu.
    void add_about(Main_window&);

    // View context menu.
    void add_switch_to_image_view(View&, View_factory&, View_manager&);
    void add_switch_to_dataset_view(View&, View_factory&, View_manager&);
};
