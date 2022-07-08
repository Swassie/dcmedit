#pragma once
#include "ui/new_file_dialog/INew_file_view.h"

#include <QWidget>

class New_file_view : public INew_file_view
{
public:
    New_file_view(QWidget*);

    fs::path show_file_dialog() override;
    void show_error(const std::string&) override;

private:
    QWidget* m_parent;
};
