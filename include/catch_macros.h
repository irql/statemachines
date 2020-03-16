template<typename T> struct _args {
    T v1, v2;
};

template<> struct _args<bool> { bool v1 = true, v2 = false; };
template<> struct _args<std::string> { std::string v1 = "¶µ±¼Ø☭", v2 = "A bit of a strange test string."; };
