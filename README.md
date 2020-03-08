# The future of the state machine

A finite state machine (finite state automata) is the mathematical representation of some system which may assume any one of a number of finite states based on the edges (transitions) which connect that state to one or more other states, in a unidirectional fashion, where each state transition is initiated through some classifiable, finite, global input. There is no theoretical limit on the number of discrete states (nodes), nor the number of discrete state transitions (edges).

Of course, the state machine is a useful concept to leverage in building, monitoring and maintaining distributed systems, when the state of the system as a whole is only understood through the aggregation of the individual state of each of its constituents. But is it possible to transfer the understanding of this principle into a machine, i.e. can we program a computer to autonomously plan, build, and test new distributed software, along with its corresponding infrastructure?

The true barrier to automation of any kind is not simply the ability to programmatically perform the task, but the ability to programmatically validate that the expected result occurs with the highest possible degree of accuracy, and if it deviates, report the difference to the highest possible degree of precision. For software and infrastructure that is already deployed, having a live monitoring system is paramount to application health and stability for this reason. But for software and infrastructure that is not deployed, and not yet designed, is it possible to use machine learning to optimize the design of any service or infrastructure by allowing the computer to model their components using interconnected webs of asynchronous finite state machines, i.e. for a single machine to be able to accurately predict the state of an enire distributed system?

## Data structures

### State Machines

```
template <class T>
class StateMachine {
    State *current_state;

    void input(T t) {
        current_state = current_state->input(t);
    };
};
```

### States

```
template <class T>
class State {
    std::vector<struct edge> edges;
    std::queue<struct transition> transitions;
    State<T> *input(T t) {
        for(auto edge : edges) {
            if(edge->transition(t)) {
                transitions.push({&this, edge});
                return edge->next;
            }
        }
        return NULL;
    };
};
```

### Edges

```
template <class T>
struct edge {
    unsigned long latency, next;
    bool<T> (*)(T) transition;
};
```

### Transitions
template <class T>
struct transition {
    struct edge edge;
    State *old;
};

The edges between all other nodes

| XXXX XXXX | YYYY YYYY | ZZZZ ZZZZ | @@@@ @@@@ |
| State ID  | Latency   | Next Node | func_ptr  |
