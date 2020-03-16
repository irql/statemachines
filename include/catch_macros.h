template<typename T> struct _args {
    T v1, v2;
};

#ifdef _TEST_MACHINE

template<> struct _args<bool> { bool v1 = true; };
template<> struct _args<std::string> { std::string v1 = "¶µ±¼Ø☭"; };

#endif

#ifdef _TEST_MACHINE_RUNTIME

template<> struct _args<bool> { bool v1 = true, v2 = false; };
template<> struct _args<std::string> { const std::string v1 = "¶µ±¼Ø☭", v2 = "A bit of a strange test string."; };

#endif
