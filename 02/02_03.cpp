#include <iostream>
#include <memory>
using namespace std;

template<typename T>
class SinglyLinkedListNode {
public:
    T value;
    unique_ptr<SinglyLinkedListNode<T>> next;

    SinglyLinkedListNode(T val) : value(val), next(nullptr) {};
};

template<typename T>
class SinglyLinkedList {
public:
    unique_ptr<SinglyLinkedListNode<T>> first;

    SinglyLinkedList(T val)
        : first(new SinglyLinkedListNode<T>(val)) {
    };

    void unshift(T val) {
        unique_ptr<SinglyLinkedListNode<T>> newly(new SinglyLinkedListNode<T>(val));
        newly->next = move(first);
        first = move(newly);
    }
};

int main() {
    cout << "instantiate" << endl;
    SinglyLinkedList<int> list(10);
    cout << list.first->value << endl;

    cout << "add" << endl;
    list.unshift(20);
    cout << list.first->value << endl;

    list.unshift(30);
    list.unshift(40);

    cout << "iterate..." << endl;
    for (auto it = list.first.get(); it != nullptr; it = it->next.get()) {
        cout << it->value << endl;
    }
}
