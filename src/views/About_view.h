#pragma once
#include "views/IAbout_view.h"

#include <QDialog>

class About_view : public QDialog, public IAbout_view
{
    Q_OBJECT
public:
    About_view(QWidget*);

    void show_about_dialog() override;
};
