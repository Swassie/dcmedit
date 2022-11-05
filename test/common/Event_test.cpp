#include "common/Callback_ref.h"
#include "common/Event.h"
#include "common/Scoped_defer.h"
#include "common/Scoped_disable.h"

#include <catch2/catch.hpp>
#include <string>

TEST_CASE("Adding event callback.") {
    Event<> event;

    SECTION("adding a callback works.") {
        int counter = 0;
        event.add_callback([&] {
            counter++;
        });

        event();

        CHECK(counter == 1);
	}

    SECTION("if an event callback adds another callback, the new callback is also run.") {
        int counter[] = {0, 0};
        event.add_callback([&] {
            counter[0]++;
            event.add_callback([&] {counter[1]++;});
        });

        event();

        CHECK(counter[0] == 1);
        CHECK(counter[1] == 1);
	}
}

TEST_CASE("Removing event callback.") {
    Event<> event;

    SECTION("removing a callback works.") {
        int counter = 0;
        Callback_ref callback = event.add_callback([&] {
            counter++;
        });

        event();

        CHECK(counter == 1);

        callback.remove_callback();
        event();

        CHECK(counter == 1);
	}

    SECTION("if event callback removes itself, the rest of the callbacks are unaffected.") {
        int counter[] = {0, 0};
        Callback_ref callback = event.add_callback([&] {
            callback.remove_callback();
            counter[0]++;
        });
        event.add_callback([&] {
            counter[1]++;
        });

        event();
        CHECK(counter[0] == 1);
        CHECK(counter[1] == 1);

        event();
        CHECK(counter[0] == 1);
        CHECK(counter[1] == 2);
	}

    SECTION("if event callback removes a previous callback, the rest of the callbacks are unaffected.") {
        int counter[] = {0, 0, 0};
        Callback_ref callback = event.add_callback([&] {
            counter[0]++;
        });
        event.add_callback([&] {
            callback.remove_callback();
            counter[1]++;
        });
        event.add_callback([&] {
            counter[2]++;
        });

        event();
        CHECK(counter[0] == 1);
        CHECK(counter[1] == 1);
        CHECK(counter[2] == 1);

        event();
        CHECK(counter[0] == 1);
        CHECK(counter[1] == 2);
        CHECK(counter[2] == 2);
	}

    SECTION("if event callback removes the next callback, the next callback is not run.") {
        int counter[] = {0, 0, 0};
        Callback_ref callback;
        event.add_callback([&] {
            callback.remove_callback();
            counter[0]++;
        });
        callback = event.add_callback([&] {
            counter[1]++;
        });
        event.add_callback([&] {
            counter[2]++;
        });

        event();
        CHECK(counter[0] == 1);
        CHECK(counter[1] == 0);
        CHECK(counter[2] == 1);

        event();
        CHECK(counter[0] == 2);
        CHECK(counter[1] == 0);
        CHECK(counter[2] == 2);
	}
}

TEST_CASE("Event with parameters.") {
    Event<int, double&, const std::string&, bool*> event;
    event.add_callback([] (int i, double& d, const std::string& s, bool* b) {
        CHECK(i == 10);
        CHECK(d == 1.5);
        CHECK(s == "foo");
        CHECK(*b == true);

        d = 5.5;
        *b = false;
    });

    double dd = 1.5;
    bool bb = true;
    event(10, dd, "foo", &bb);

    CHECK(dd == 5.5);
    CHECK(bb == false);
}

TEST_CASE("Disable event") {
    Event<> event;
    int counter = 0;
    event.add_callback([&] {
        counter++;
    });
    CHECK(event.enabled());
    CHECK(!event.deferred());

    event.enable_event(false);

    CHECK(!event.enabled());
    CHECK(!event.deferred());

    event();
    event();

    CHECK(event.deferred());
    CHECK(counter == 0);

    event.enable_event(true);
    CHECK(event.enabled());
    CHECK(!event.deferred());

    event();
    CHECK(!event.deferred());
    CHECK(counter == 1);
}

TEST_CASE("Adding more than 65536 callbacks causes Event_error to be thrown") {
    Event<> event;

    for(int i = 0; i < 65536; i++) {
        event.add_callback([] {});
    }

    REQUIRE_THROWS_AS(event.add_callback([] {}), Event_error);
}

TEST_CASE("Adding and removing more than 65536 callbacks works") {
    Event<> event;
    Callback_ref callback;

    for(int i = 0; i < 65540; i++) {
        callback = event.add_callback([] {});
        callback.remove_callback();
    }
}

TEST_CASE("During a single event, an added callback will be called, despite that it gets the same ID as a deleted, already called callback") {
    Event<> event;
    Callback_ref callback = event.add_callback([] {});

    for(int i = 0; i < 65534; i++) {
        event.add_callback([] {});
    }

    int counter = 0;
    event.add_callback([&] {
        callback.remove_callback();
        event.add_callback([&] {counter++;});
    });

    // Make sure all ID's are allocated.
    REQUIRE_THROWS_AS(event.add_callback([] {}), Event_error);

    event();
    CHECK(counter == 1);
}

TEST_CASE("Callbacks are called in chronological order, regardless of ID") {
    Event<> event;
    Callback_ref callback;

    for(int i = 0; i < 35540; i++) {
        callback = event.add_callback([] {});
        callback.remove_callback();
    }
    std::string result = "";
    event.add_callback([&] {result += "foo";});

    for(int i = 0; i < 35540; i++) {
        callback = event.add_callback([] {});
        callback.remove_callback();
    }
    event.add_callback([&] {result += "bar";});

    event();
    CHECK(result == "foobar");
}

TEST_CASE("Event is disabled while triggered, to prevent resursive events") {
    Event<> event;
    int counter = 0;
    event.add_callback([&] {
        counter++;
        event();
    });

    event();
    CHECK(counter == 1);
}

TEST_CASE("Only the outer scoped defer has effect for nested scopes") {
    Event<> event;
    int counter = 0;
    event.add_callback([&] {
        counter++;
    });
    {
        Scoped_defer defer_1(event);
        {
            Scoped_defer defer_2(event);
            {
                Scoped_disable disable(event);
                event();
                CHECK(counter == 0);
            }
            event();
            CHECK(counter == 0);
        }
        event();
        CHECK(counter == 0);
    }
    CHECK(event.enabled());
    CHECK(!event.deferred());
    CHECK(counter == 1);
}

TEST_CASE("Only the outer scoped disable has effect for nested scopes") {
    Event<> event;
    int counter = 0;
    event.add_callback([&] {
        counter++;
    });
    {
        Scoped_disable disable_1(event);
        {
            Scoped_disable disable_2(event);
            {
                Scoped_defer defer(event);
                event();
                CHECK(counter == 0);
            }
            event();
            CHECK(counter == 0);
        }
        event();
        CHECK(counter == 0);
    }
    CHECK(event.enabled());
    CHECK(!event.deferred());
    CHECK(counter == 0);
}
