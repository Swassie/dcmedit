#include "common/Event.h"
#include "common/Scoped_callbacks.h"

#include <catch2/catch.hpp>

TEST_CASE("Scoped callbacks are removed when the scope object is destroyed") {
    Event<> event;
    int counter = 0;
    {
        Scoped_callbacks scope;
        Callback_ref callback = event.add_callback([&] {
            counter++;
        });
        scope.add_to_scope(callback);
        event();
        CHECK(counter == 1);
    }

    event();
    CHECK(counter == 1);
}
