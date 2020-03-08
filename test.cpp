#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <class T> class State;

template <class T>
class Edge {
    private:
        int latency;
        State<T> *target;

    public:
        Edge(int latency, State<T> *target);
};

template <class T>
class State {
    private:
        vector<Edge<T>> *edges;

    public:
        State(vector<Edge<T>> *edges);
};

template <class T>
class Transition {
};

template <class T>
class StateMachine {
    private:
        vector<Transition<T>> history;
        State<T> *current_state;

    public:
        StateMachine(State<T> *initial_state);
        void progress(T input);
};

template <class T> Edge<T>::Edge(int latency, State<T> *target) {
    this->latency = latency;
    this->target = target;
}

template <class T> State<T>::State(vector<Edge<T>> *edges) {
    this->edges = edges;
}

template <class T> StateMachine<T>::StateMachine(State<T> *initial) {
    this->current_state = initial;
}

int main(int argc, char **argv) {
    return 0;
}
