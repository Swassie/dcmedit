#include "ui/about_dialog/About_view.h"

#include "common/App_info.h"

#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>

static QString get_about_text();

About_view::About_view(QWidget* parent)
    : QDialog(parent) {
    auto layout = new QVBoxLayout(this);
    auto text = new QLabel(get_about_text());
    text->setTextFormat(Qt::RichText);
    text->setOpenExternalLinks(true);
    text->setTextInteractionFlags(Qt::TextSelectableByMouse | Qt::LinksAccessibleByMouse);
    text->setMargin(10);

    auto scroll_area = new QScrollArea();
    scroll_area->setBackgroundRole(QPalette::Light);
    scroll_area->setWidget(text);
    layout->addWidget(scroll_area);
    setWindowTitle("About");
}

void About_view::show_about_dialog() {
    exec();
}

static QString get_about_text() {
    QString text = R"END(
<h1>dcmedit</h1>
dcmedit is a DICOM editor for Windows, Linux and macOS.<br>
<br>
Version: $VERSION<br>
<br>
Copyright 2020-2022 Marcus Swanson<br>
<br>
This program is free software: you can redistribute it and/or modify<br>
it under the terms of the GNU General Public License as published by<br>
the Free Software Foundation, either version 3 of the License, or<br>
(at your option) any later version.<br>
<br>
This program is distributed in the hope that it will be useful,<br>
but WITHOUT ANY WARRANTY; without even the implied warranty of<br>
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the<br>
GNU General Public License for more details.<br>
<br>
You should have received a copy of the GNU General Public License<br>
along with this program.  If not, see https://www.gnu.org/licenses/.<br>
<br>
The code can be found on <a href="https://github.com/Swassie/dcmedit">GitHub</a>.
Bugs can be reported on GitHub or via <a href="mailto:marcus.swanson91@gmail.com">mail</a>.

<h2>Third-party libraries</h2>
This program includes the following free and open-source software (FOSS) libraries:

<h3>DCMTK</h3>
Copyright (C) 1994-2019, OFFIS e.V.<br>
All rights reserved.

<h3>Material icons</h3>
The Material icons are available under Apache license version 2.0.

<h3>Qt</h3>
The Qt Toolkit is Copyright (C) 2017 The Qt Company Ltd.<br>
Contact: https://www.qt.io/licensing<br>
<br>
You may use, distribute and copy the Qt GUI Toolkit under the terms of<br>
GNU Lesser General Public License version 3, which supplements<br>
GNU General Public License Version 3.<br>
<br>

Copies of the licenses are distributed together with this program.<br>
<br>
<b>Additionally, the following open-source libraries were used during development:</b>

<h3>Catch2</h3>
https://github.com/catchorg/Catch2

<h3>Trompeloeil</h3>
https://github.com/rollbear/trompeloeil
)END";
    text.replace("$VERSION", App_info::version);
    return text;
}
