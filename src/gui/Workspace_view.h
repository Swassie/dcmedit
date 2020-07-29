#pragma once
#include <QWidget>
#include <vector>

class DcmFileFormat;

class Workspace_view : public QWidget
{
    Q_OBJECT

public:
    Workspace_view(DcmFileFormat&);
    void setup();

    void set_view_count(size_t count);

private:
    void create_layout();
    void create_1_view_layout();
    void create_2_view_layout();
    void create_3_view_layout();
    void create_4_view_layout();
    void create_5_view_layout();
    void create_6_view_layout();

    DcmFileFormat& m_dicom_file;
    std::vector<QWidget*> m_views;
};
