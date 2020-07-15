#pragma once
#include <dcmtk/dcmdata/dctk.h>
#include <dcmtk/dcmimgle/dcmimage.h>
#include <memory>
#include <string>
#include <vector>

class Dataset
{
public:
    static std::unique_ptr<Dataset> load_files(const std::vector<std::string>& file_paths);

    std::vector<DcmFileFormat*> get_files();

private:
    std::vector<std::unique_ptr<DcmFileFormat>> m_files;
};
