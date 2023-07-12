#pragma once
#include "ui/startup_view/IStartup_view.h"

#include <QWidget>

class Startup_view : public QWidget, public IStartup_view
{
    Q_OBJECT
public:
    Startup_view();
};
