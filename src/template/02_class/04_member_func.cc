template <typename T>
struct ClassTemplate {
    void f(T) {}    
};


template <typename T>
struct ClassTemplate2 {
    template<typename... Args>
    void f(Args&&... args) {
    }
};

struct Test {
    template <typename... Args>
    void f(Args&&... args) {
    }
};




