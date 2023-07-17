#include "ui/Gui_util.h"

QString Gui_util::get_tag_path_help() {
    return "Enter tag path. The syntax is '{sequence[item-nr].}*element', "
        "e.g. '0010,0010' or '(0008,1111)[0].PatientName'. "
        "The item number starts from zero and can be replaced by a wildcard '*', "
        "which selects all items in a sequence. More info can be found "
        "on https://support.dcmtk.org/docs/dcmodify.html";
}
