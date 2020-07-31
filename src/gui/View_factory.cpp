#include "gui/View_factory.h"

#include "gui/Image_view.h"
#include "gui/Pan_tool.h"
#include "gui/Zoom_tool.h"

View_factory::View_factory(DcmFileFormat& dicom_file, Tool_bar& tool_bar)
    : m_dicom_file(dicom_file),
      m_tool_bar(tool_bar) {}

std::unique_ptr<QWidget> View_factory::make_view() const {
    return std::make_unique<Image_view>(m_dicom_file,
                                        m_tool_bar,
                                        std::make_unique<Pan_tool>(),
                                        std::make_unique<Zoom_tool>());
}
