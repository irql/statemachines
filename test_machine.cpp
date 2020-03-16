#define _TEST_MACHINE
#include <catch2/catch.hpp>

#include "include/catch_macros.h"
#include "include/machine.hpp"

TEMPLATE_TEST_CASE("nop machine", "[machine]", bool, std::string) {
    static _args<TestType> args;

    std::vector<machine::Edge<TestType>> edges;
    machine::State<TestType> state_inf("nop", &edges);
    edges.push_back(machine::Edge<TestType>(5, &state_inf, [](TestType input) -> bool { return true; }));
    machine::Machine<TestType> machine_nop("nop", &state_inf);

    SECTION("transition") {
        machine_nop.progress(args.v1);
        REQUIRE(machine_nop.walk().previous->getName() == state_inf.getName());
    }
}

#undef _TEST_MACHINE
