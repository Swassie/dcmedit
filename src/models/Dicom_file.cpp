#include "Dicom_file.h"

#include "logging/Log.h"

#include <dcmtk/dcmdata/dcdeftag.h>
#include <dcmtk/dcmdata/dcmetinf.h>
#include <dcmtk/dcmdata/dcuid.h>
#include <dcmtk/dcmdata/dcxfer.h>
#include <stdexcept>

Dicom_file::Dicom_file(const fs::path& path)
    : m_path(path),
      m_unsaved_changes(false) {
    if(!OFStandard::fileExists(path.c_str())) {
        throw std::runtime_error("file not found");
    }
    OFCondition status = m_file.loadFile(path.c_str());

    if(status.bad()) {
        throw std::runtime_error(status.text());
    }
    Log::debug("Loaded file: " + m_path.string());
}

bool Dicom_file::is_dicomdir() {
    DcmMetaInfo* meta_info = m_file.getMetaInfo();

    if(meta_info == nullptr) {
        return false;
    }

    OFString media_storage;
    meta_info->findAndGetOFString(DCM_MediaStorageSOPClassUID, media_storage);

    return media_storage == UID_MediaStorageDirectoryStorage;
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
        throw std::runtime_error(status.text());
    }
    m_path = path;
    m_unsaved_changes = false;
    Log::debug("Saved file: " + path.string());
}

void Dicom_file::create_new_file(const fs::path& path) {
    DcmFileFormat file;
    OFCondition status = file.saveFile(path.c_str(), EXS_LittleEndianExplicit);

    if(status.bad()) {
        throw std::runtime_error(status.text());
    }
}
