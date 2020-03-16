#define _TEST_MACHINE_RUNTIME
#include "catch2/catch.hpp"

#include "include/catch_macros.h"
#include "include/machine/runtime.hpp"

TEMPLATE_TEST_CASE("machine::runtime::Stack push and pop works", "[runtime]", bool, std::string) {
    machine::runtime::Stack<TestType> stack_api;
    machine::runtime::Base<TestType>  &t_api = stack_api;

    static _args<TestType> args;

    SECTION("Push pop, push push pop pop...") {
        t_api.dispatch("push", args.v1);
        REQUIRE( args.v1 == t_api.dispatch("pop").at(0) );

        t_api.dispatch("push", args.v1);
        t_api.dispatch("push", args.v2);
        REQUIRE( args.v2 == t_api.dispatch("pop").at(0) );
        REQUIRE( args.v1 == t_api.dispatch("pop").at(0) );

        t_api.dispatch("push", args.v1);
        t_api.dispatch("push", args.v2);
        t_api.dispatch("push", args.v2);
        t_api.dispatch("push", args.v1);

        REQUIRE( args.v1 == t_api.dispatch("pop").at(0) );
        REQUIRE( args.v2 == t_api.dispatch("pop").at(0) );
        REQUIRE( args.v2 == t_api.dispatch("pop").at(0) );
        REQUIRE( args.v1 == t_api.dispatch("pop").at(0) );
    }
}
