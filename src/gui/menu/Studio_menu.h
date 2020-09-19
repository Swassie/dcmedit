#pragma once
#include <QMenu>

class Main_window;

class Studio_menu : public QMenu
{
public:
    enum class Studio {
        dicom,
        test
    };

    Studio_menu();

    void add_studios(Main_window&, Studio);
};
