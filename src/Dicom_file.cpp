#include "Dicom_file.h"

#include "Exceptions.h"
#include "logging/Log.h"

Dicom_file::Dicom_file(const std::string& path)
    : m_path(path),
      m_unsaved_changes(false) {
    OFCondition status;

    if(OFStandard::fileExists(m_path.c_str())) {
        status = m_file.loadFile(m_path.c_str());
    }
    else {
        throw DcmeditException("File not found: " + m_path);
    }
    if(status.bad()) {
        throw DcmeditException("Failed to load file: " + m_path +
                               "\nReason: " + status.text());
    }
    Log::debug("Loaded file: " + m_path);
}

void Dicom_file::save_file() {
    save_file_as(m_path);
}

void Dicom_file::save_file_as(const std::string& path) {
    OFCondition status = m_file.getDataset()->loadAllDataIntoMemory();

    if(status.good()) {
        status = m_file.saveFile(path.c_str());
    }
    if(status.bad()) {
        throw DcmeditException("Failed to save file: " + path +
                               "\nReason: " + status.text());
    }
    m_path = path;
    m_unsaved_changes = false;
    Log::debug("Saved file: " + path);
}
