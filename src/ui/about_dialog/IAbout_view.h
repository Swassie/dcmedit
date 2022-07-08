#pragma once

class IAbout_view
{
public:
    virtual ~IAbout_view() = default;

    virtual void show_about_dialog() = 0;
};
