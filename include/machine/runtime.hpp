#ifndef RUNTIME_HPP_INCLUDED
#define RUNTIME_HPP_INCLUDED

#include <stack>

namespace machine::runtime {

template <typename T, typename ouT=T>
class Base {
public:
    virtual std::vector<ouT> dispatch(std::string method, std::vector<T> args) = 0;

    std::vector<ouT> dispatch(std::string method) {
        return this->dispatch(method, std::vector<T>());
    }

    std::vector<ouT> dispatch(std::string method, T arg) {
        return this->dispatch(method, std::vector<T>{arg});
    }
};

template <class T>
class Stack : virtual public Base<T> {
private:
    std::stack<T> stack;

public:
    std::vector<T> dispatch(std::string method, std::vector<T> args) {
        if(method == "push") {
            this->stack.push(args.at(0));
            return std::vector<T>();
        } else if(method == "pop") {
            T top = this->stack.top();
            this->stack.pop();
            return std::vector<T>{top};
        }
        return std::vector<T>();
    }
};

} // end namespace
#endif
