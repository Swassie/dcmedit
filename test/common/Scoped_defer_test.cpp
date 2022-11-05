#include "common/Event.h"
#include "common/Scoped_defer.h"

#include <catch2/catch.hpp>

TEST_CASE("Nothing happends if the event isn't triggered while deferred") {
    Event<> event;
    int counter = 0;
    event.add_callback([&] {
        counter++;
    });
    {
        Scoped_defer defer(event);
        CHECK(!event.enabled());
    }
    CHECK(event.enabled());
    CHECK(counter == 0);
}

TEST_CASE("The event is triggered a single time when the scope ends if triggered while deferred") {
    Event<> event;
    int counter = 0;
    event.add_callback([&] {
        counter++;
    });
    {
        Scoped_defer defer(event);
        event();
        event();
        event();
        CHECK(counter == 0);
    }
    CHECK(counter == 1);
}
