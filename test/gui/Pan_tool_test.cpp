#include "gui/Pan_tool.h"

#include "catch.hpp"
#include <QMouseEvent>

SCENARIO("Testing Pan_tool") {

    GIVEN("a pan tool") {
        Pan_tool pan_tool;

		WHEN("pressing the left mouse and moving the mouse") {
            pan_tool.mouse_press({QEvent::MouseButtonPress, {10, 20},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            pan_tool.mouse_move({QEvent::MouseMove, {100, 200},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

			THEN("the pan tool reports the correct values") {
				REQUIRE(pan_tool.get_x() == 90);
                REQUIRE(pan_tool.get_y() == 180);
			}
		}

        WHEN("doing multiple panning moves") {
            pan_tool.mouse_press({QEvent::MouseButtonPress, {10, 20},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            pan_tool.mouse_move({QEvent::MouseMove, {100, 200},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

            pan_tool.mouse_move({QEvent::MouseMove, {50, 500},
                    Qt::NoButton, Qt::NoButton, Qt::NoModifier});

            pan_tool.mouse_press({QEvent::MouseButtonPress, {50, 100},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            pan_tool.mouse_move({QEvent::MouseMove, {-20, 50},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

			THEN("the pan tool reports the correct values") {
				REQUIRE(pan_tool.get_x() == 20);
                REQUIRE(pan_tool.get_y() == 130);
			}
		}
	}
}
