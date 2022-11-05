#include "common/Event.h"
#include "common/Scoped_disable.h"

#include <catch2/catch.hpp>

TEST_CASE("Nothing happends if the event isn't triggered while disabled") {
    Event<> event;
    int counter = 0;
    event.add_callback([&] {
        counter++;
    });
    {
        Scoped_disable disable(event);
        CHECK(!event.enabled());
    }
    CHECK(event.enabled());
    CHECK(counter == 0);
}

TEST_CASE("Nothing happends if the event is triggered while disabled") {
    Event<> event;
    int counter = 0;
    event.add_callback([&] {
        counter++;
    });
    {
        Scoped_disable disable(event);
        event();
        event();
        event();
    }
    CHECK(counter == 0);
}
