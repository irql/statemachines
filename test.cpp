#include <iostream>
#include <string>

#include "include/machine.hpp"

using namespace machine;
using namespace std;

int main(int argc, char **argv) {

    // http://bit.ly/2TBhvdf
    //
    // Machine<string> nop has one State named "base", which has
    // one Edge that always transitions back into itself
    // no matter what the input is.
    //
    vector<Edge<string>> base_edges;

    State<string> base("nop", &base_edges);

    base_edges.push_back(Edge<string>(10, &base, [](string input){
                return true;
            }));

    MACHINE(string, nop, &base);

    nop.progress("test");
    nop.progress("test");
    nop.progress("test");
    nop.progress("test");
    nop.progress("test");

    nop.debug_history();

    // http://bit.ly/2TzOiPH
    //
    // Machine<bool> flip_flop has two States named "on" and "off",
    // and four Edge objects defined across these states; one
    // Edge object transitions from "on" to "off" on an input
    // of true, one additional object transitions from "off" to
    // "on" on true, and two additional objects transition from
    // "on" to "on" and "off" back to "off" upon an input of
    // false, respectively.
    //
    vector<Edge<bool>> on_edges, off_edges;
    State<bool> on("on", &on_edges), off("off", &off_edges);

    auto g_true = [](bool input) {
        return input == true;
    };
    auto g_false = [](bool input) {
        return input == false;
    };
    auto s_hello = [](bool input, Runtime<bool> *runtime) -> void {
        cout << "Hello from side_effect" << endl;
    };

    // on -[true]->  off
    on_edges.push_back(Edge<bool>(15, &off, g_true, s_hello));
    // on -[false]-> on
    on_edges.push_back(Edge<bool>(15, &on, g_false, s_hello));

    // off -[true]->  on
    off_edges.push_back(Edge<bool>(15, &on, g_true, s_hello));
    // off -[false]-> off
    off_edges.push_back(Edge<bool>(15, &off, g_false, s_hello));

    // It is initialized in the "on" state.
    MACHINE(bool, flip_flop, &on);

    flip_flop.progress(false);
    flip_flop.progress(true);
    flip_flop.progress(false);
    flip_flop.progress(true);

    flip_flop.debug_history();

    return 0;
}
