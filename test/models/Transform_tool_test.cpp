#include "models/Transform_tool.h"

#include <catch2/catch.hpp>

#include <QMouseEvent>
#include <QTransform>

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
				CHECK(transform.m31() == 90);
                CHECK(transform.m32() == 180);
                CHECK(transform.m11() == 1);
                CHECK(transform.m22() == 1);
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
				CHECK(transform.m31() == 20);
                CHECK(transform.m32() == 130);
                CHECK(transform.m11() == 1);
                CHECK(transform.m22() == 1);
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
				CHECK(transform.m31() == 8);
                CHECK(transform.m32() == 16);
                CHECK(transform.m11() == Approx(0.2));
                CHECK(transform.m22() == Approx(0.2));
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
				CHECK(transform.m31() == Approx(-97.7).epsilon(0.1));
                CHECK(transform.m32() == Approx(-195.4).epsilon(0.1));
                CHECK(transform.m11() == Approx(2.2));
                CHECK(transform.m22() == Approx(2.2));
			}
		}
	}
}
