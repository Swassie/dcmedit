#pragma once
#include "gui/tool/Transform_tool.h"
#include "gui/view/View.h"

#include <memory>
#include <QWidget>

class Dataset_model;
class Tool;
class Tool_bar;

class Image_view : public View
{
    Q_OBJECT
public:
    Image_view(Dataset_model&, Tool_bar&, std::unique_ptr<Transform_tool>);

    void set_dataset_model(Dataset_model&) override;

private:
    void paintEvent(QPaintEvent*) override;
    void mouseMoveEvent(QMouseEvent*) override;
    void mousePressEvent(QMouseEvent*) override;

    void set_tool();

    Dataset_model* m_dataset_model;
    Tool_bar& m_tool_bar;
    Tool* m_current_tool;
    std::unique_ptr<Transform_tool> m_transform_tool;
};
