#include "Dicom_file.h"

#include "common/Status.h"
#include "logging/Log.h"
#include <dcmtk/dcmdata/dcxfer.h>

Dicom_file::Dicom_file()
    : m_unsaved_changes(false) {}

Status Dicom_file::load_file(const fs::path& path) {
    if(!OFStandard::fileExists(path.c_str())) {
        return Status("file not found");
    }
    OFCondition status = m_file.loadFile(path.c_str());

    if(status.bad()) {
        return Status::from(status);
    }
    m_path = path;
    m_unsaved_changes = false;
    Log::debug("Loaded file: " + path.string());

    return Status::ok;
}

Status Dicom_file::save_file() {
    return save_file_as(m_path);
}

Status Dicom_file::save_file_as(const fs::path& path) {
    OFCondition status = m_file.getDataset()->loadAllDataIntoMemory();

    if(status.good()) {
        E_TransferSyntax original_transfer = m_file.getDataset()->getOriginalXfer();
        E_TransferSyntax new_transfer = original_transfer != EXS_Unknown ? original_transfer : EXS_LittleEndianExplicit;
        status = m_file.saveFile(path.c_str(), new_transfer);
    }
    if(status.bad()) {
        return Status::from(status);
    }
    m_path = path;
    m_unsaved_changes = false;
    Log::debug("Saved file: " + path.string());

    return Status::ok;
}

Status Dicom_file::create_new_file(const fs::path& path) {
    DcmFileFormat file;
    OFCondition status = file.saveFile(path.c_str(), EXS_LittleEndianExplicit);

    return Status::from(status);
}
