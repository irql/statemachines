#ifndef RUNTIME_HPP_INCLUDED
#define RUNTIME_HPP_INCLUDED

namespace machine::runtime {

template <class T> class Runtime;

template <class T>
class Runtime {
    std::vector<T> dispatch(std::string method, std::vector<T> args) {
        throw std::runtime_error("You must override Runtime<T>::dispatch().");
    }
};

template <class T>
class RuntimeStack : public Runtime<T> {
    private:
        std::stack<T> stack;

    public:
        std::vector<T> dispatch(std::string method, std::vector<T> args) {
            if(method == "mirror") {
                return args;
            } else {
                return std::vector<T>();
            }
        }
};

} // end namespace
#endif
