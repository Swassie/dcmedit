#pragma once
#include "gui/view/View.h"
#include "gui/tool/Transform_tool.h"

#include <memory>
#include <QWidget>

class DcmFileFormat;
class Tool;
class Tool_bar;

class Image_view : public View
{
    Q_OBJECT
public:
    Image_view(DcmFileFormat&,
               Tool_bar&,
               std::unique_ptr<Transform_tool>);

private:
    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

    void set_tool();

    DcmFileFormat& m_dicom_file;
    Tool_bar& m_tool_bar;
    Tool* m_current_tool;
    std::unique_ptr<Transform_tool> m_transform_tool;
};
