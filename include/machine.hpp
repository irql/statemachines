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

template <class T> class Transition;
template <class T> class Machine;
template <class T> class State;
template <class T> class Edge;

template <class T>
class Edge {
    public:
        int latency;
        State<T> *target;

        bool (*transition)(T input) = NULL; // MAXIMUM DANGER
        void (*side_effect)(T input, runtime::Runtime<T> *runtime) = NULL;

        Edge(int latency, State<T> *target, bool (*transition)(T input)) {
            this->latency = latency;
            this->target = target;
            this->transition = transition;

            if(this->transition == NULL) {
                throw std::runtime_error("The Transition<T>::transition() function pointer cannot be null.");
            }
        }

        Edge (
            int      latency,
            State<T> *target,
            bool     (*transition)(T input),
            void     (*side_effect)(T input, runtime::Runtime<T> *runtime)
        ) :
            Edge ( latency, target, transition )
        {
            this->side_effect = side_effect;
        }
};

template <class T>
class State {
    private:
        std::vector<Edge<T>> *edges;
        std::string name;
        int id = 0;

    public:
        Transition<T> *transition(T input, runtime::Runtime<T> *runtime) {
            for(Edge<T> e : *this->edges) {
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

        State(std::string name, std::vector<Edge<T>> *edges) {
            this->edges = edges;
            this->name = name;

            if(this->edges == NULL) {
                throw std::runtime_error("State<T>::edges cannot be null.");
            }
        }
};

template <class T>
class Transition {
    public:
        State<T> *previous;
        State<T> *current;
        int latency;
        T input;

        Transition(State<T> *previous, State<T> *current, T input, int latency) {
            this->previous = previous;
            this->current = current;
            this->latency = latency;
            this->input = input;
        }
};

template <class T>
class Machine {
    private:
        std::queue<Transition<T>> history;
        State<T> *current_state;
        int state_count = 0;
        runtime::Runtime<T> runtime;
        std::string name;

    public:

        void progress(T input) {
            Transition<T> *t = this->current_state->transition(input, &runtime);
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

        void debug_history() {
            std::cout << name << ":" << typeid(this).name() << std::endl;
            for(int i = 0; !history.empty();) {
                Transition<T> t = history.front();
                history.pop();
                i += t.latency;
                std::cout <<
                    t.previous->getName() << ":" << t.previous->getId() << "\t-[" << t.input << "]-> " <<
                    t.current->getName() << ":" << t.current->getId() << ",\t" <<
                    i << "ns,\t" << t.latency << "ns" << std::endl;
            }
            std::cout << std::endl;
        }

        Machine(std::string name, State<T> *initial) {
            this->current_state = initial;
            this->name = name;
        }

        Machine(std::string name, runtime::Runtime<T> runtime, State<T> *initial) {
            this->current_state = initial;
            this->runtime = runtime;
            this->name = name;
        }
};

} // end namespace
#endif
