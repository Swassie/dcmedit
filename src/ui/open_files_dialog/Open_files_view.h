#pragma once
#include "ui/open_files_dialog/IOpen_files_view.h"

#include <QWidget>

class Open_files_view : public IOpen_files_view
{
public:
    Open_files_view(QWidget*);

    std::vector<fs::path> show_file_dialog() override;
    void show_error(const std::vector<std::string>&) override;
    std::unique_ptr<IProgress_view> create_progress_view() override;

private:
    QWidget* m_parent;
};
