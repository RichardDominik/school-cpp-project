/**
    main.h
    Project: Calculator of prefix, infix and postfix expressions with variables and Parentheses

    @author Richard Dominik
    @version 1.0.0
*/

#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <vector>

using namespace std;

class Exception {
    string message;
public:
    Exception(const string &str) {this->message = str;};
    string getMessage() const { return this->message; };
};

class ExpressionError : public Exception {
public:
    ExpressionError(const string &str) : Exception(str) {};
};

template <typename T> class Stack {
    // stack parameters
    T* stackArray;
    int stackCount;
    int stackMaxSize;
    // resize parameters and initial max size
    static const int growthFactor = 2;
    static const int initialMaxSize = 10;
public:
    Stack();
    inline Stack(const Stack<T> &rhs) { *this = rhs; }
    Stack(int maxSize);
    ~Stack();
    void pop();
    inline bool empty() { return stackCount == 0; }
    void push(T data);
    //getters
    inline T& getTop() { return this->empty() ? throw underflow_error("Underflow Exception") : stackArray[stackCount - 1]; }
    inline int getSize() { return stackCount; }
private:
    void init();
    void increaseArraySize();
};

template <class T>
Stack<T>::Stack() : stackCount(0), stackMaxSize(initialMaxSize)
{
    init();
}

template <class T>
Stack<T>::Stack(int maxSize) : stackCount(0), stackMaxSize(initialMaxSize)
{
    init();
}

template <class T>
Stack<T>::~Stack()
{
    delete [] stackArray;
}

template <class T>
void Stack<T>::init()
{
    stackArray = new T[stackMaxSize];
    stackCount = 0;
}

template <class T>
void Stack<T>::increaseArraySize()
{
    stackMaxSize = growthFactor * stackMaxSize;
    T* tmp = new T[stackMaxSize];

    for(int i = 0; i < stackCount; i++)
        tmp[i] = stackArray[i];

    delete [] stackArray;

    stackArray = tmp;
}

template <class T>
void Stack<T>::push(T data)
{
    if(stackCount == stackMaxSize)
        increaseArraySize();
    stackArray[stackCount++] = data;
}

template <class T>
void Stack<T>::pop()
{
    if(stackCount == 0)
        throw underflow_error("Underflow Exception");
    stackCount--;
}

class Expression {
    // map of results which are loaded from file
    map<string, int> resultOfExpressions;
    map<string, string> variables;
public:
    bool assignVariable(const string &variableName, const string &expression);
    bool isNumber(const string &element);
    bool isOperator(const string &element);
    int getPriorityOfOperator(const string &inputOperator);
    void removeSpaces(string &str1);
    string getStringFromChar(const char &el);
    int compute(const string &expression);
    int computePostfix(const string &expression);
    int computePrefix(const string &expression);
    vector<string> splitToItems(const string &expression);
    string infixToPostfix(const string &infixExpression);
    string getStringWithoutWhiteSpaces(const string &str);
    bool readFromFile(const string &fileName);
    bool saveToFile(const string &fileName);
    string getNthLineFromFile(const string &fileName, int indexOfLine);
};