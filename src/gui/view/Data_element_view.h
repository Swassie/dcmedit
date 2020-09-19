#pragma once
#include "gui/view/View.h"

class Data_element_model;

class Data_element_view : public View
{
    Q_OBJECT
public:
    Data_element_view(Data_element_model&);
};
