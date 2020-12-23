#include "Dicom_file.h"

#include "logging/Log.h"

#include <dcmtk/ofstd/ofcond.h>
#include <dcmtk/ofstd/ofstd.h>
#include <stdexcept>

Dicom_file::Dicom_file(std::string &path)
    : m_path(path) {
    OFCondition status;
    if(OFStandard::fileExists(m_path.c_str())) {
        status = m_file.loadFile(m_path.c_str());
    }
    else {
        throw std::runtime_error("File not found: " + m_path);
    }
    if(status.bad()) {
        throw std::runtime_error("Failed to load file: " + m_path +
                                 ". Reason: " + status.text());
    }
    Log::debug("Loaded file: " + m_path);
}
