#include <catch2/catch.hpp>

#include "include/catch_macros.h"
#include "include/machine.hpp"

TEMPLATE_TEST_CASE("nop machine", "[machine]", bool, std::string, int) {
    static _args<TestType> args;

    std::vector<machine::Edge<TestType>> edges;
    machine::runtime::Nop<TestType> nop_runtime;
    machine::State<TestType> state_inf("nop", &edges);

    edges.push_back(machine::Edge<TestType>(5, &state_inf, [](TestType input) -> bool { return true; }));

    machine::Machine<TestType> machine_nop("nop", &state_inf, nop_runtime);

    SECTION("transition") {
        machine_nop.progress(args.v1);
        REQUIRE(machine_nop.walk().previous->getName() == state_inf.getName());
        machine_nop.progress(args.v1);
        REQUIRE(machine_nop.walk().previous->getName() == state_inf.getName());
    }

    machine::runtime::Stack<TestType> stack_api;
    std::vector<machine::Edge<TestType>> pp_edges;
    machine::State<TestType> pp_state("pp_nop", &pp_edges);
    machine::Machine<TestType> machine_pp("pp", &pp_state, stack_api);

    // You must ensure that all possible transitions are defined by the edges.
    // Note that there must also be a one to one correlation between edge and
    // potential activation / transition in the function domain. That means,
    // there must always be a catch-all.
    pp_edges.push_back(machine::Edge<TestType>(6, &pp_state, [](TestType input) -> bool {
                if(input == args.v1) {
                    return true;
                }
                return false;
            }, [](TestType input, machine::runtime::Base<TestType> &runtime) -> void {
                runtime.dispatch("push", args.v2);
            }));
    pp_edges.push_back(machine::Edge<TestType>(6, &pp_state, [](TestType input) -> bool {
                if(input != args.v1) {
                    return true;
                }
                return false;
            }, [](TestType input, machine::runtime::Base<TestType> &runtime) -> void {
                runtime.dispatch("pop");
            }));

    SECTION("stack machine") {
        machine_pp.progress(args.v1);
        machine_pp.progress(args.v2);
        REQUIRE(stack_api.tos == args.v2);
    }
}
