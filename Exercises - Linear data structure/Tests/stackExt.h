# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
	stack<T> values;
	stack<T> minimums;
public:
	StackExt() {};
	bool empty() const; 
	T& top();
	void pop();
	void push(const T& val);
	T& findMin();
};

//=============================================================================
// Exercise 3: StackExt class
//=============================================================================
//TODO
template <class T>
bool StackExt<T>::empty() const {
    return true;
}

//TODO
template <class T>
T& StackExt<T>::top() {
    T* x = new T();
    return *x;
}

//TODO
template <class T>
void StackExt<T>::pop() {
}

//TODO
template <class T>
void StackExt<T>::push(const T& val) {
}

//TODO
template <class T>
T& StackExt<T>::findMin() {
    T* x = new T();
    return *x;
}
