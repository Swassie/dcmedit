#pragma once
#include "ui/open_folder_dialog/IOpen_folder_view.h"

#include <QWidget>

class Open_folder_view : public IOpen_folder_view
{
public:
    Open_folder_view(QWidget*);

    fs::path show_dir_dialog() override;
    std::unique_ptr<IProgress_view> create_progress_view() override;

private:
    QWidget* m_parent;
};
