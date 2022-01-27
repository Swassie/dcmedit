#pragma once
#include "views/IOpen_files_view.h"

class QWidget;

class Open_files_view : public IOpen_files_view
{
public:
    Open_files_view(QWidget*);

    QStringList show_file_dialog() override;
    void show_error(const QStringList&) override;

private:
    QWidget* m_parent;
};
