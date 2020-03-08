#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <queue>

using namespace std;

template <class T> class State;
template <class T> class Transition;

template <class T>
class Edge {
    public:
        int latency;
        State<T> *target;

        bool (*transition)(T input) = NULL; // MAXIMUM DANGER

        Edge(int latency, State<T> *target, bool (*transition)(T input)) {
            this->latency = latency;
            this->target = target;
            this->transition = transition;

            if(this->transition == NULL) {
                throw runtime_error("The Transition<T>::transition() function pointer cannot be null.");
            }
        }
};

template <class T>
class State {
    private:
        vector<Edge<T>> *edges;
        string name;
        int id = 0;

    public:
        Transition<T> *transition(T input) {
            for(Edge<T> e : *this->edges) {
                if(e.transition(input)) {
                    return new Transition<T>(this, e.target, e.latency);
                }
            }
            return NULL;
        };

        // Only allow the id to be set once
        // This is only used for debugging
        void setId(int id) {
            if(this->id == 0) {
                this->id = id;
            }
        };

        int getId() { return id; };

        string getName() { return name; };

        State(string name, vector<Edge<T>> *edges) {
            this->edges = edges;
            this->name = name;

            if(this->edges == NULL) {
                throw runtime_error("State<T>::edges cannot be null.");
            };
        }
};

template <class T>
class Transition {
    public:
        State<T> *previous;
        State<T> *current;
        int latency;

        Transition(State<T> *previous, State<T> *current, int latency) {
            this->previous = previous;
            this->current = current;
            this->latency = latency;
        };
};

template <class T>
class Machine {
    private:
        State<T> *current_state;
        int state_count = 0;
        string name;

    public:
        queue<Transition<T>> history;

        void progress(T input) {
            // Assign each state a numeric id in the order in which
            // it is encountered as the machine is progressed.

            Transition<T> *t = this->current_state->transition(input);
            if(t == NULL) {
                throw runtime_error("The transition returned by State<T>::transition(T) cannot be null.");
            } else {
                history.push(*t);
                for(auto s : array<State<T>*, 2>{this->current_state, t->current}) {
                    if(s->getId() == 0)
                        s->setId(++state_count);
                }
                this->current_state = t->current;
            }
        }

        void debug_history() {
            cout << name << ":" << typeid(this).name() << endl;
            for(int i = 0; !history.empty();) {
                Transition<T> t = history.front();
                history.pop();
                i += t.latency;
                cout <<
                    t.previous->getName() << ":" << t.previous->getId() << "\t-> " <<
                    t.current->getName() << ":" << t.current->getId() << ",\t" <<
                    i << "ns,\t" << t.latency << "ns" << endl;
            }
            cout << endl;
        };

        Machine(string name, State<T> *initial) {
            this->current_state = initial;
            this->name = name;
        }
};

int main(int argc, char **argv) {
    // Machine "nop" has one State named "base", which has
    // one Edge that always transitions back into itself
    // no matter what the input is.
    vector<Edge<string>> base_edges;

    State<string> base("nop", &base_edges);

    base_edges.push_back(Edge<string>(10, &base, [](string input){
                return true;
            }));

    Machine<string> nop("nop", &base);

    nop.progress("test");
    nop.progress("test");
    nop.progress("test");
    nop.progress("test");
    nop.progress("test");

    nop.debug_history();

    // Machine "flip_flop" has two States named "on" and "off."
    //
    vector<Edge<bool>> on_edges, off_edges;
    State<bool> on("on", &on_edges), off("off", &off_edges);

    auto g_true = [](bool input) {
        return input == true;
    };
    auto g_false = [](bool input) {
        return input == false;
    };

    on_edges.push_back(Edge<bool>(15, &off, g_true));
    on_edges.push_back(Edge<bool>(15, &on, g_false));

    off_edges.push_back(Edge<bool>(15, &on, g_true));
    off_edges.push_back(Edge<bool>(15, &off, g_false));

    // It is initialized in the "on" state.
    Machine<bool> flip_flop("flip_flop", &on);

    flip_flop.progress(false);
    flip_flop.progress(true);
    flip_flop.progress(false);
    flip_flop.progress(true);

    flip_flop.debug_history();

    return 0;
}
