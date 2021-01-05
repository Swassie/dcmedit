#include "gui/About_dialog.h"

#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

static QString get_about_text();

About_dialog::About_dialog(QWidget* parent)
    : QDialog(parent) {
    auto layout = new QVBoxLayout(this);
    auto text = new QLabel(get_about_text());
    text->setTextFormat(Qt::MarkdownText);
    text->setOpenExternalLinks(true);
    text->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse);

    auto scroll_area = new QScrollArea();
    scroll_area->setBackgroundRole(QPalette::Light);
    scroll_area->setWidget(text);
    layout->addWidget(scroll_area);
}

static QString get_about_text() {
    return
        R"END(
# dcmedit
Copyright 2020, 2021 Marcus Swanson

The code can be found on [GitHub](https://github.com/Swassie/dcmedit).
Bugs can be reported on GitHub or via [mail](mailto:marcus.swanson91@gmail.com).

This program uses the following open-source libraries:

## DCMTK
```
Copyright (C) 1994-2019, OFFIS e.V.
All rights reserved.
```

## Material icons
The Material icons are available under Apache license version 2.0.

## Qt
```
The Qt Toolkit is Copyright (C) 2017 The Qt Company Ltd.
Contact: https://www.qt.io/licensing

You may use, distribute and copy the Qt GUI Toolkit under the terms of
GNU Lesser General Public License version 3, which supplements GNU General
Public License Version 3.
```
)END";
}
