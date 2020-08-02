#pragma once
#include "gui/Pan_tool.h"
#include "gui/Menu.h"
#include "gui/Zoom_tool.h"

#include <memory>
#include <QWidget>

class DcmFileFormat;
class Tool;
class Tool_bar;

class Image_view : public QWidget
{
    Q_OBJECT

public:
    Image_view(DcmFileFormat&,
               std::unique_ptr<Menu>,
               Tool_bar&,
               std::unique_ptr<Pan_tool>,
               std::unique_ptr<Zoom_tool>);

private:
    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void contextMenuEvent(QContextMenuEvent*) override;

    void set_tool();

    DcmFileFormat& m_dicom_file;
    std::unique_ptr<Menu> m_menu;
    Tool_bar& m_tool_bar;
    Tool* m_current_tool;
    std::unique_ptr<Pan_tool> m_pan_tool;
    std::unique_ptr<Zoom_tool> m_zoom_tool;
};
