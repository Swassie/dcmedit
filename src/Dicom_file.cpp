#include "Dicom_file.h"

#include "Exceptions.h"
#include "logging/Log.h"
#include <dcmtk/dcmdata/dcxfer.h>

Dicom_file::Dicom_file(const fs::path& path)
    : m_path(path),
      m_unsaved_changes(false) {
    OFCondition status;

    if(OFStandard::fileExists(m_path.c_str())) {
        status = m_file.loadFile(m_path.c_str());
    }
    else {
        throw DcmeditException("File not found: " + m_path.string());
    }
    if(status.bad()) {
        throw DcmeditException("Failed to load file: " + m_path.string() +
                               "\nReason: " + status.text());
    }
    Log::debug("Loaded file: " + m_path.string());
}

void Dicom_file::save_file() {
    save_file_as(m_path);
}

void Dicom_file::save_file_as(const fs::path& path) {
    OFCondition status = m_file.getDataset()->loadAllDataIntoMemory();

    if(status.good()) {
        E_TransferSyntax original_transfer = m_file.getDataset()->getOriginalXfer();
        E_TransferSyntax new_transfer = original_transfer != EXS_Unknown ? original_transfer : EXS_LittleEndianExplicit;
        status = m_file.saveFile(path.c_str(), new_transfer);
    }
    if(status.bad()) {
        throw DcmeditException("Failed to save file: " + path.string() +
                               "\nReason: " + status.text());
    }
    m_path = path;
    m_unsaved_changes = false;
    Log::debug("Saved file: " + path.string());
}

void Dicom_file::create_new_file(const fs::path& path) {
    DcmFileFormat file;
    OFCondition status = file.saveFile(path.c_str(), EXS_LittleEndianExplicit);

    if(status.bad()) {
        throw DcmeditException("Failed to create file: " + path.string() +
                               "\nReason: " + status.text());
    }
}
