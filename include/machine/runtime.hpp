#ifndef RUNTIME_HPP_INCLUDED
#define RUNTIME_HPP_INCLUDED

namespace machine::runtime {

template <class T> class Runtime;

template <class T>
class Base {
public:
    virtual std::vector<T> dispatch(std::string method, std::vector<T> args) = 0;

    std::vector<T> dispatch(std::string method) {
        return this->dispatch(method, std::vector<T>());
    }

    std::vector<T> dispatch_one(std::string method, T arg) {
        return this->dispatch(method, std::vector<T>{arg});
    }

    T dispatch_one(std::string method) {
        return this->dispatch(method).at(0);
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
