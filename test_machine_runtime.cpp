#include "catch2/catch.hpp"

#include "include/machine/runtime.hpp"

template<typename T> struct _args {
    const T v1, v2;
};

#define _DEF_ARGS(T, _v1, _v2) \
    template<> struct _args<T> { T v1 = _v1, v2 = _v2; }

_DEF_ARGS(bool, true, false);
_DEF_ARGS(std::string, "A bit of a strange test string.", "¶µ±¼Ø☭");

TEMPLATE_TEST_CASE("machine::runtime::Stack push and pop works", "[runtime]", bool, std::string) {
    machine::runtime::Stack<TestType> stack_api;
    machine::runtime::Base<TestType>  &t_api = stack_api;

    struct _args<TestType> args;

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
