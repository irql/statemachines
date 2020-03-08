#include <iostream>
#include <string>
#include <vector>
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

    public:
        Transition<T> *transition(T input);

        State(vector<Edge<T>> *edges) {
            this->edges = edges;

            if(this->edges == NULL) {
                throw runtime_error("State<T>::edges cannot be null.");
            }
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

    public:
        queue<Transition<T>> history;

        void progress(T input);
        void debug_history() {
            for(int i = 0; !history.empty();) {
                Transition<string> t = history.front();
                history.pop();
                i += t.latency;
                cout << t.previous << ", " << t.current << ", " << i << "ns" << endl;
            }
        };

        Machine(State<T> *initial) {
            this->current_state = initial;
        }
};

template <class T> Transition<T> *State<T>::transition(T input) {
    for(Edge<T> e : *this->edges) {
        if(e.transition(input)) {
            return new Transition<T>(this, e.target, e.latency);
        }
    }
    return NULL;
}

template<> void Machine<string>::progress(string input) {
    Transition<string> *t = this->current_state->transition(input);
    if(t == NULL) {
        throw runtime_error("The transition returned by State<T>::transition(T) cannot be null.");
    } else {
        history.push(*t);
        this->current_state = t->current;
    }
}

int main(int argc, char **argv) {
    // Machine "nop" has one State named "base", which has
    // one Edge that always transitions back into itself
    // no matter what the input is.
    vector<Edge<string>> base_edges;
    State<string> base(&base_edges);
    base_edges.push_back(Edge<string>(10, &base, [](string input){
                return true;
            }));
    Machine<string> nop(&base);
    nop.progress("test");
    nop.progress("test");
    nop.progress("test");
    nop.progress("test");
    nop.progress("test");

    nop.debug_history();

    return 0;
}
