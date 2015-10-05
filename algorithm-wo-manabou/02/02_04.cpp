#include <list>
using namespace std;

template<typename T>
class Stack {
private:
    list<T> values;

public:
    void push(T v) {
        values.push_back(v);
    }

    T pop() {
        T ret(values.back());
        values.pop_back();
        return ret;
    }
};

template<typename T>
class Queue {
private:
    list<T> values;

public:
    void enqueue(T v) {
        values.push_front(v);
    }

    T dequeue() {
        T ret(values.back());
        values.pop_back();
        return ret;
    }
};
