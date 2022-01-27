#pragma once

class QMouseEvent;

class Tool
{
public:
    virtual ~Tool() = default;

    /** Handler for mouse events.
     *  The return value tells if the state of the tool has changed.
     */
    virtual bool mouse_move(const QMouseEvent&) = 0;
    virtual bool mouse_press(const QMouseEvent&) = 0;
};
