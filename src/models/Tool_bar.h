#pragma once

class Tool_bar
{
public:
    enum class Tool {
        pan,
        zoom
    };

    Tool_bar();

    Tool get_selected_tool() const {return m_selected_tool;}
    void set_selected_tool(Tool tool) {m_selected_tool = tool;}

protected:
    Tool m_selected_tool;
};
