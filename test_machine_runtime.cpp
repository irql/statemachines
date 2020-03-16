#include "catch2/catch.hpp"

#include "include/machine/runtime.hpp"

TEST_CASE("machine::runtime::Stack<bool> sanity", "[runtime]") {
    machine::runtime::Stack<bool> stack_api;
    machine::runtime::Base<bool> &bool_api = stack_api;
    SECTION("Push and a pop") {
        bool_api.dispatch("push", true);
        REQUIRE( bool_api.dispatch("pop").at(0) );

        bool_api.dispatch("push", true);
        bool_api.dispatch("push", false);

        REQUIRE( !bool_api.dispatch("pop").at(0) );
        REQUIRE( bool_api.dispatch("pop").at(0) );
    }
}
