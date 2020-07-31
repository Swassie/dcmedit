#include "gui/Zoom_tool.h"

#include "catch.hpp"
#include <cmath>
#include <QMouseEvent>

static bool is_equal(double a, double b, double epsilon) {
    return std::abs(a - b) < epsilon;
}

SCENARIO("Testing Zoom_tool") {

    GIVEN("a zoom tool") {
        Zoom_tool zoom_tool;

		WHEN("pressing the left mouse and moving the mouse") {
            zoom_tool.mouse_press({QEvent::MouseButtonPress, {10, 20},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            zoom_tool.mouse_move({QEvent::MouseMove, {100, 200},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

			THEN("the zoom tool reports the correct values") {
				REQUIRE(is_equal(zoom_tool.get_zoom_factor(), 0.2, 0.01));
			}
		}

        WHEN("doing multiple zooming moves") {
            zoom_tool.mouse_press({QEvent::MouseButtonPress, {10, 20},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            zoom_tool.mouse_move({QEvent::MouseMove, {100, 200},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

            zoom_tool.mouse_move({QEvent::MouseMove, {50, 500},
                    Qt::NoButton, Qt::NoButton, Qt::NoModifier});

            zoom_tool.mouse_press({QEvent::MouseButtonPress, {50, 100},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            zoom_tool.mouse_move({QEvent::MouseMove, {-20, -50},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

			THEN("the zoom tool reports the correct values") {
                REQUIRE(is_equal(zoom_tool.get_zoom_factor(), 1.7, 0.01));
			}
		}
	}
}
