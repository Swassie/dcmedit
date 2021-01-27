#pragma once
#include "gui/tool/Transform_tool.h"
#include "gui/view/View.h"

#include <memory>
#include <QWidget>

class Dicom_studio;
class Tool;
class Tool_bar;

class Image_view : public View
{
    Q_OBJECT
public:
    Image_view(Dicom_studio&, Tool_bar&, std::unique_ptr<Transform_tool>);

private:
    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

    void set_tool();

    Dicom_studio& m_studio;
    Tool_bar& m_tool_bar;
    Tool* m_current_tool;
    std::unique_ptr<Transform_tool> m_transform_tool;
};
