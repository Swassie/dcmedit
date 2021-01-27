#pragma once
#include <memory>
#include <vector>

class Dicom_file;
class QMouseEvent;
class QWidget;

namespace Gui_util
{
    bool is_left_mouse_pressed(const QMouseEvent&);
    bool should_unsaved_changes_be_discarded(QWidget*);
    std::vector<std::unique_ptr<Dicom_file>> load_files(QWidget*);
}
