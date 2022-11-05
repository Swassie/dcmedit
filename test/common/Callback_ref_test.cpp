#include "common/Callback_ref.h"
#include "common/Event.h"

#include <catch2/catch.hpp>

TEST_CASE("Destroying the callback reference does not remove the callback.") {
    Event<> event;
    int counter = 0;
    {
        Callback_ref callback = event.add_callback([&] {
            counter++;
        });
    }

    event();

    CHECK(counter == 1);
}

TEST_CASE("Testing remove_callback()") {
    Event<> event;
    int counter = 0;
    Callback_ref callback = event.add_callback([&] {
        counter++;
    });

    SECTION("The callback can be removed via the reference") {
        callback.remove_callback();
        event();
        CHECK(counter == 0);
    }

    SECTION("Removing the callback multiple times does nothing") {
        callback.remove_callback();
        callback.remove_callback();
        event();
        CHECK(counter == 0);
    }
}
