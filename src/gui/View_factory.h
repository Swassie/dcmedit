#pragma once
#include <memory>
#include <QWidget>

class DcmFileFormat;
class Tool_bar;

class View_factory
{
public:
    View_factory(DcmFileFormat&, Tool_bar&);

    std::unique_ptr<QWidget> make_view() const;

private:
    DcmFileFormat& m_dicom_file;
    Tool_bar& m_tool_bar;
};
