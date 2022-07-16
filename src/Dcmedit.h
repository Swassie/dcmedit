#pragma once
#include "models/Tool_bar.h"
#include "ui/IView_factory.h"
#include "ui/file_tree_view/File_tree_presenter.h"
#include "ui/main_view/Main_presenter.h"
#include "ui/split_view/Split_factory.h"
#include "ui/split_view/Split_presenter.h"

class Dcmedit
{
public:
    Dcmedit(IView_factory&);

private:
    IMain_view& m_main_view;
    Dicom_files m_dicom_files;
    Tool_bar m_tool_bar;
    Dataset_model m_dataset_model;
    File_tree_model m_file_tree_model;
    Split_factory m_split_factory;
    Split_presenter m_split_presenter;
    File_tree_presenter m_file_tree_presenter;
    Main_presenter m_main_presenter;
};
