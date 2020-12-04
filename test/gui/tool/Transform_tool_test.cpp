#include "gui/tool/Transform_tool.h"

#include "catch.hpp"

#include <cmath>
#include <QMouseEvent>
#include <QTransform>

static bool is_equal(double a, double b, double epsilon) {
    return std::abs(a - b) < epsilon;
}

SCENARIO("Testing Transform_tool") {

    GIVEN("a transform tool in translate mode") {
        Transform_tool transform_tool;
        transform_tool.set_translate_mode();

		WHEN("pressing the left mouse and moving the mouse") {
            transform_tool.mouse_press({QEvent::MouseButtonPress, {10, 20},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            transform_tool.mouse_move({QEvent::MouseMove, {100, 200},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

			THEN("the tool reports the correct values") {
                QTransform transform = transform_tool.get_transform();
				REQUIRE(transform.m31() == 90);
                REQUIRE(transform.m32() == 180);
                REQUIRE(transform.m11() == 1);
                REQUIRE(transform.m22() == 1);
			}
		}

        WHEN("doing multiple translation moves") {
            transform_tool.mouse_press({QEvent::MouseButtonPress, {10, 20},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            transform_tool.mouse_move({QEvent::MouseMove, {100, 200},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

            transform_tool.mouse_move({QEvent::MouseMove, {50, 500},
                    Qt::NoButton, Qt::NoButton, Qt::NoModifier});

            transform_tool.mouse_press({QEvent::MouseButtonPress, {50, 100},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            transform_tool.mouse_move({QEvent::MouseMove, {-20, 50},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

			THEN("the tool reports the correct values") {
                QTransform transform = transform_tool.get_transform();
				REQUIRE(transform.m31() == 20);
                REQUIRE(transform.m32() == 130);
                REQUIRE(transform.m11() == 1);
                REQUIRE(transform.m22() == 1);
			}
		}
	}

    GIVEN("a transform tool in scale mode") {
        Transform_tool transform_tool;
        transform_tool.set_scale_mode();

		WHEN("pressing the left mouse and moving the mouse") {
            transform_tool.mouse_press({QEvent::MouseButtonPress, {10, 20},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            transform_tool.mouse_move({QEvent::MouseMove, {100, 200},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

			THEN("the tool reports the correct values") {
                QTransform transform = transform_tool.get_transform();
				REQUIRE(transform.m31() == 8);
                REQUIRE(transform.m32() == 16);
                REQUIRE(is_equal(transform.m11(), 0.2, 0.01));
                REQUIRE(is_equal(transform.m22(), 0.2, 0.01));
			}
		}

        WHEN("doing multiple scaling moves") {
            transform_tool.mouse_press({QEvent::MouseButtonPress, {10, 20},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            transform_tool.mouse_move({QEvent::MouseMove, {100, 50},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

            transform_tool.mouse_move({QEvent::MouseMove, {50, 200},
                    Qt::NoButton, Qt::NoButton, Qt::NoModifier});

            transform_tool.mouse_press({QEvent::MouseButtonPress, {50, 100},
                    Qt::LeftButton, Qt::NoButton, Qt::NoModifier});

            transform_tool.mouse_move({QEvent::MouseMove, {-20, -50},
                    Qt::NoButton, Qt::LeftButton, Qt::NoModifier});

			THEN("the tool reports the correct values") {
                QTransform transform = transform_tool.get_transform();
				REQUIRE(is_equal(transform.m31(), -97.7, 0.1));
                REQUIRE(is_equal(transform.m32(), -195.4, 0.1));
                REQUIRE(is_equal(transform.m11(), 2.2, 0.01));
                REQUIRE(is_equal(transform.m22(), 2.2, 0.01));
			}
		}
	}
}
