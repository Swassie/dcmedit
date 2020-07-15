#pragma once

class Main_window;
class Workspace_view;

class Menu_bar
{
public:
    static void create_file_menu(Main_window&);
    static void create_view_menu(Main_window&, Workspace_view&);
};
