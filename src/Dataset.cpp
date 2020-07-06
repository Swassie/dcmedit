#include "Dataset.h"
#include "logging/Log.h"

Dataset Dataset::load_files(const std::vector<std::string>& file_paths) {
    Dataset dataset;
    OFString series_uid;
    for(const std::string file_path : file_paths) {
        auto file_format = std::make_unique<DcmFileFormat>();
        OFCondition status = file_format->loadFile(file_path.c_str());

        if(!status.good()) {
            Log::info("Could not load file: " + file_path +
                      ". Reason: " + status.text());
            continue;
        }
        if(series_uid.empty()) {
            file_format->getDataset()->findAndGetOFString(DCM_SeriesInstanceUID,
                                                          series_uid);
            dataset.m_files.push_back(std::move(file_format));
        }
        else {
            OFString series_uid_temp;
            file_format->getDataset()->findAndGetOFString(DCM_SeriesInstanceUID,
                                                          series_uid_temp);
            if(series_uid == series_uid_temp) {
                dataset.m_files.push_back(std::move(file_format));
            }
            else {
                Log::info("Series UID differs, ignoring file: " + file_path);
            }
        }
    }
    return dataset;
}

std::vector<DcmFileFormat*> Dataset::get_files() {
    std::vector<DcmFileFormat*> files;
    files.reserve(m_files.size());
    for(const auto& file : m_files) {
        files.push_back(file.get());
    }
    return files;
}
