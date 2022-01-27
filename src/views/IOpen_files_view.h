#pragma once
class QStringList;

class IOpen_files_view
{
public:
    ~IOpen_files_view() = default;

    virtual QStringList show_file_dialog() = 0;
    virtual void show_error(const QStringList&) = 0;
};
