#ifndef MACHINE_HPP_INCLUDED
#define MACHINE_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <queue>
#include <stack>

#include "machine/runtime.hpp"

#define STRINGIFY(X) #X
#define MACHINE(x, y, z) Machine<x> y(STRINGIFY(y), z);

namespace machine {

template <typename T> class Transition;
template <typename T> class Machine;
template <typename T> class State;
template <typename T> class Edge;

template <typename T>
class Edge {
    public:
        int latency;
        State<T> *target;

        bool (*transition)(T input) = NULL; // MAXIMUM DANGER
        void (*side_effect)(T input, runtime::Base<T> &runtime) = NULL;

        Edge(int t, State<T> *tg, bool (*tr)(T input), void (*s)(T, runtime::Base<T>&)) : latency(t), target(tg), transition(tr), side_effect(s) {
            if(this->transition == NULL) {
                throw std::runtime_error("The Transition<T>::transition() function pointer cannot be null.");
            }
        }

        Edge(int t, State<T> *tg, bool (*tr)(T)) : Edge(t, tg, tr, nullptr) {}
};

template <typename T>
class State {
    private:
        std::string name;
        int id = 0;

    public:
        std::vector<Edge<T>> edges;

        Transition<T> *transition(T input, runtime::Base<T> &runtime) {
            for(Edge<T> e : this->edges) {
                if(e.transition(input)) {
                    if(e.side_effect != NULL) {
                        e.side_effect(input, runtime);
                    }
                    return new Transition<T>(this, e.target, input, e.latency);
                }
            }
            return NULL;
        }

        // Only allow the id to be set once, relative to the complete
        // history of state transitions taken by the Machine object.
        // This is only used for debugging
        void setId(int id) {
            if(this->id == 0) {
                this->id = id;
            }
        }

        int getId() { return id; }

        std::string getName() { return name; }

        State(std::string n) : name(n) { }
};

template <typename T>
class Transition {
    public:
        State<T> *previous;
        State<T> *current;
        int latency;
        T input;

        Transition(State<T> *ps, State<T> *cs, T i, int t) : previous(ps), current(cs), latency(t), input(i) {}
};

template <typename T>
class Machine {
    private:
        std::queue<Transition<T>> history;
        State<T> *current_state;
        int state_count = 0;
        runtime::Base<T> &runtime;
        std::string name;

    public:

        Transition<T> &walk(void) {
            Transition<T> &next = history.front();
            history.pop();
            return next;
        }

        void progress(T input) {
            Transition<T> *t = this->current_state->transition(input, runtime);
            if(t == NULL) {
                throw std::runtime_error("The transition returned by State<T>::transition(T) cannot be null.");
            } else {
                history.push(*t);
                // Assign each state a numeric id in the order in which
                // it is encountered as the machine is progressed.
                for(auto s : std::array<State<T>*, 2>{this->current_state, t->current}) {
                    if(s->getId() == 0)
                        s->setId(++state_count);
                }
                this->current_state = t->current;
            }
        }

        Machine(std::string n, State<T> *cs, runtime::Base<T> &r) : current_state(cs), runtime(r), name(n) {}
};

} // end namespace
#endif
