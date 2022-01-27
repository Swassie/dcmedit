#include "common/Event.h"

#include "catch/catch.hpp"

TEST_CASE("Adding event handler.") {

    Event<> event;

    SECTION("adding a handler works.") {
        int counter = 0;
        event += [&] {
            counter++;
        };

        event();

        CHECK(counter == 1);
	}

    SECTION("if an event handler adds another handler, the new handler is also run.") {
        int counter[] = {0, 0};
        event += [&] {
            counter[0]++;
            event += [&] {counter[1]++;};
        };

        event();

        CHECK(counter[0] == 1);
        CHECK(counter[1] == 1);
	}
}

TEST_CASE("Removing event handler.") {

    Event<> event;

    SECTION("removing a handler works.") {
        int counter = 0;
        event += [&] {
            counter++;
        };

        event();

        CHECK(counter == 1);

        event.remove_handler(0);
        event();

        CHECK(counter == 1);
	}

    SECTION("if event handler removes itself, the rest of the handlers are unaffected.") {
        int counter[] = {0, 0};
        event += [&] {
            event.remove_handler(0);
            counter[0]++;
        };
        event += [&] {
            counter[1]++;
        };

        event();

        CHECK(counter[0] == 1);
        CHECK(counter[1] == 1);
	}

    SECTION("if event handler removes a previous handler, the rest of the handlers are unaffected.") {
        int counter[] = {0, 0, 0};
        event += [&] {
            counter[0]++;
        };
        event += [&] {
            event.remove_handler(0);
            counter[1]++;
        };
        event += [&] {
            counter[2]++;
        };

        event();

        CHECK(counter[0] == 1);
        CHECK(counter[1] == 1);
        CHECK(counter[2] == 1);
	}

    SECTION("if event handler removes the next handler, the next handler is not run.") {
        int counter[] = {0, 0, 0};
        event += [&] {
            event.remove_handler(1);
            counter[0]++;
        };
        event += [&] {
            counter[1]++;
        };
        event += [&] {
            counter[2]++;
        };

        event();

        CHECK(counter[0] == 1);
        CHECK(counter[1] == 0);
        CHECK(counter[2] == 1);
	}
}

TEST_CASE("Event with parameters.") {

    Event<int, double> event;

    SECTION("the event arguments are passed to the handlers.") {
        event += [] (int i, double d) {
            CHECK(i == 10);
            CHECK(d == 1.5);
        };

        event(10, 1.5);
	}
}
