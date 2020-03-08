# The future of the state machine

A finite state machine (finite state automata) is the mathematical representation of some system which may assume any one of a number of finite states based on the edges (transitions) which connect that state to one or more other states, in a unidirectional fashion, where each state transition is initiated through some classifiable, finite, global input. There is no theoretical limit on the number of discrete states (nodes), nor the number of discrete state transitions (edges).

Of course, the state machine is a useful concept to leverage in building, monitoring and maintaining distributed systems, when the state of the system as a whole is only understood through the aggregation of the individual state of each of its constituents. But is it possible to transfer the understanding of this principle into a machine, i.e. can we program a computer to autonomously plan, build, and test new distributed software, along with its corresponding infrastructure?

The true barrier to automation of any kind is not simply the ability to programmatically perform the task, but the ability to programmatically validate that the expected result occurs with the highest possible degree of accuracy, and if it deviates, report the difference to the highest possible degree of precision. For software and infrastructure that is already deployed, having a live monitoring system is paramount to application health and stability for this reason. But for software and infrastructure that is not deployed, and not yet designed, is it possible to use machine learning to optimize the design of any service or infrastructure by allowing the computer to model their components using interconnected webs of asynchronous finite state machines, i.e. for a single machine to be able to accurately predict the state of an enire distributed system?

## Classes

### Machine

Contains the current state the machine is in, and keeps a record of all `Transition` objects generated each time `Machine::progress()` is run.

### State

Contains a vector of `Edge` objects, each of which describe one possible transition from this state into another.

### Edge

Contains a reference to another state, along with a function pointer to a function called with the input to `Machine::progress()` that should return true if and only if the other state should be entered into.

### Transition

Contains a reference to the previous state and the current state, in addition to the latency incurred by making the transition.
