/**
    main.cpp
    Project: Calculator of prefix, infix and postfix expressions with variables and Parentheses

    @author Richard Dominik
    @version 1.0.0
*/

#include <iostream>
#include <iterator>
#include <map>
#include <string>
#include <stdlib.h>
#include <vector>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <regex>
#include "main.h"

using namespace std;

/// Method to check if string can be converted to integer
/// \param element
/// \return bool
bool Expression::isNumber(const string &element) {
    try {
        int number = stoi(element);
        return true;
    } catch(...){
        return false;
    }
}

/// Method to check if string is operator
/// \param element
/// \return bool
bool Expression::isOperator(const string &element) {
    for(int i = 0; i < element.length(); i++){
        if(element[i] == '+' || element[i] == '-' || element[i] == '*' ||
           element[i] == '/' || element[i] == '%')
            return true;
    }

    return false;
}

/// Method to assing variable to map of variables
/// \param variableName
/// \param expression
/// \return bool
bool Expression::assignVariable(const string &variableName, const string &expression) {
    bool isInVariables = false;
    int i;
    try {
        i = stoi(expression);
    } catch (...){
        if(variables.count(expression)){
            isInVariables = true;
            for(auto &h: variables)
                if(h.first == expression)
                    i = stoi(h.second);
        }

        if(!isInVariables)
            i = this->compute(expression);
    }

    variables.insert(pair<string,string>(variableName,to_string(i)));
    return true;
}

/// Method to compute expression, this method check if expression is valid and if is postifix, prefix or infix
/// \param expression
/// \return int
int Expression::compute(const string &expression){
    int lengthOfExpression = expression.length();
    int result;

    if(expression[0] == '+' || expression[0] == '-' || expression[0] == '*' ||
        expression[0] == '/' || expression[0] == '%'){
        result = this->computePrefix(expression);
    } else if (expression[lengthOfExpression - 1] == '+' || expression[lengthOfExpression - 1] == '-' || expression[lengthOfExpression - 1] == '*' ||
               expression[lengthOfExpression - 1] == '/' || expression[lengthOfExpression - 1] == '%'){
       result = this->computePostfix(expression);
    } else {
        if(this->isOperator(expression)){
            try {
                // if expression is infix, we want convert it to postfix
                string postfixExpression = this->infixToPostfix(expression);
                result = this->computePostfix(postfixExpression);
            } catch (...){
                throw ExpressionError("Error in expression");
            }
        } else {
            throw ExpressionError("Error in expression");
        }
    }

    return result;
}

/// Method to compute prefix expression
/// \param expression
/// \return int
int Expression::computePrefix(const string &expression){
    Stack<int> s;
    vector<string> resultExpression = this->splitToItems(expression);
    reverse(resultExpression.begin(), resultExpression.end());
    int result;

    for(auto &h: resultExpression){
        if(variables.count(h)){
            for(auto &j: variables){
                if(j.first == h)
                    h = j.second;
            }
            try {
                s.push(stoi(h));
            } catch (...){
                throw ExpressionError("Error in expression");
            }
        } else if(h == "+"){
            try {
                int x  = s.getTop() ;
                s.pop();
                int y = s.getTop();
                s.pop();
                s.push(x + y);
            } catch (...){
                throw ExpressionError("Error in expression");
            }
        } else if(h == "-"){
            try {
                int x  = s.getTop() ;
                s.pop();
                int y = s.getTop();
                s.pop();
                s.push(x - y);
            } catch (...){
                throw ExpressionError("Error in expression");
            }
        } else if(h == "*"){
            try {
                int x  = s.getTop() ;
                s.pop();
                int y = s.getTop();
                s.pop();
                s.push(x * y);
            } catch (...){
                throw ExpressionError("Error in expression");
            }
        } else if(h == "/"){
            try {
                int x = s.getTop();
                s.pop();
                int y = s.getTop();
                s.pop();

                if(y == 0)
                    throw ExpressionError("Division by Zero");

                s.push(x / y);
            } catch (ExpressionError){
                throw ExpressionError("Division by Zero");
            }
        } else if(h == "%"){
            try {
                int x = s.getTop();
                s.pop();
                int y = s.getTop();
                s.pop();
                s.push(x % y);
            } catch (...){
                throw ExpressionError("Error in expression");
            }
        } else if(this->isNumber(h)){
            s.push(stoi(h));
        }
    }

    result = s.getTop();
    s.pop();
    return result;
}

/// Method to compute Postfix expression
/// \param expression
/// \return int
int Expression::computePostfix(const string &expression){
    Stack<int> s;
    vector<string> resultExpression = this->splitToItems(expression);
    int result;

    for(auto &h: resultExpression){
        if(variables.count(h)){
            for(auto &j: variables){
                if(j.first == h)
                    h = j.second;
            }
            try {
                s.push(stoi(h));
            } catch (...){
                throw ExpressionError("Error in expression");
            }
        } else if(h == "+"){
            try {
                int x  = s.getTop() ;
                s.pop();
                int y = s.getTop();
                s.pop();
                s.push(x + y);
            } catch (...){
                throw ExpressionError("Error in expression");
            }
        } else if(h == "-"){
            try {
                int x  = s.getTop() ;
                s.pop();
                int y = s.getTop();
                s.pop();
                s.push(-x + y);
            } catch (...){
                throw ExpressionError("Error in expression");
            }
        } else if(h == "*"){
            try {
                int x  = s.getTop() ;
                s.pop();
                int y = s.getTop();
                s.pop();
                s.push(x * y);
            } catch (...){
                throw ExpressionError("Error in expression");
            }
        } else if(h == "/"){
            try {
                int y = s.getTop();
                s.pop();
                int x = s.getTop();
                s.pop();

                if(y == 0)
                    throw ExpressionError("Division by Zero");

                s.push(x / y);
            } catch (ExpressionError){
                throw ExpressionError("Division by Zero");
            }
        } else if(h == "%"){
            try {
                int y = s.getTop();
                s.pop();
                int x = s.getTop();
                s.pop();
                s.push(x % y);
            } catch (...){
                throw ExpressionError("Error in expression");
            }
        } else if(this->isNumber(h)){
            s.push(stoi(h));
        }
    }

    result = s.getTop();
    s.pop();
    return result;
}

/// Method to convert string into char, in some cases this method is usefull
/// \param el
/// \return string
string Expression::getStringFromChar(const char &el){
    string result;
    result.push_back(el);
    return result;
}

/// Method to split items from expression into vector of items
/// \param expression
/// \return vector
vector<string> Expression::splitToItems(const string &expression){
    vector<string> result;
    int i = 0;
    string copyOfExpression = expression;
    copyOfExpression += " ";

    while(copyOfExpression != " "){
        if(isalpha(copyOfExpression[i])){
            while(isalpha(copyOfExpression[i]) || this->isNumber(this->getStringFromChar(copyOfExpression[i]))){
                i++;
            }
            result.push_back(copyOfExpression.substr(0, i));
            copyOfExpression = copyOfExpression.substr(i, copyOfExpression.length() - 1);
            i = 0;
        } else if(this->isNumber(this->getStringFromChar(copyOfExpression[i]))){
            while(this->isNumber(this->getStringFromChar(copyOfExpression[i]))){
                i++;
            }
            result.push_back(copyOfExpression.substr(0, i));
            copyOfExpression = copyOfExpression.substr(i, copyOfExpression.length() - 1);
            i = 0;
        } else if(copyOfExpression[i] == ' '){
            copyOfExpression = copyOfExpression.substr(i+1, copyOfExpression.length() - 1);
            i = 0;
        } else if(copyOfExpression[i] == '-' || copyOfExpression[i] == '*' || copyOfExpression[i] == '/' ||
                copyOfExpression[i] == '+' || copyOfExpression[i] == '%' || copyOfExpression[i] == '(' || copyOfExpression[i] == ')'){
            string s;
            s.push_back(copyOfExpression[i]);
            result.push_back(s);
            copyOfExpression = copyOfExpression.substr(i+1, copyOfExpression.length() - 1);
            i = 0;
        }
    }

    return result;
}

/// Method to remove extra spaces from input string, similar to strip() function in python
/// \param str
void Expression::removeSpaces(string &str)
{
    int n = str.length();
    int i = 0, j = -1;
    bool spaceFound = false;

    while (++j < n && str[j] == ' ');

    while (j < n){
        if (str[j] != ' '){
            if ((str[j] == '.' || str[j] == ',' ||
                 str[j] == '?') && i - 1 >= 0 &&
                str[i - 1] == ' ')
                str[i - 1] = str[j++];
            else
                str[i++] = str[j++];
            spaceFound = false;
        }
        else if (str[j++] == ' ') {
            if (!spaceFound){
                str[i++] = ' ';
                spaceFound = true;
            }
        }
    }

    if (i <= 1)
        str.erase(str.begin() + i, str.end());
    else
        str.erase(str.begin() + i - 1, str.end());
}

/// Method to get priority of operator in expression
/// \param inputOperator
/// \return int
int Expression::getPriorityOfOperator(const string &inputOperator){
    if(inputOperator == "(")
        return 1;
    else if(inputOperator == "+" || inputOperator == "-")
        return 2;
    else if(inputOperator == "*" || inputOperator == "%" || inputOperator == "/")
        return 3;
    else
        return 0;
}

/// Method to convert infix expressions to postfix expressions
/// \param infixExpression
/// \return string
string Expression::infixToPostfix(const string &infixExpression) {
    Stack<string> s;
    string result = "";
    int numberOfLeftParentheses = 0;
    int numberOfRightParentheses = 0;
    vector<string> expression = this->splitToItems(infixExpression);

    for(auto h : expression){
        if(h == "(")
            numberOfLeftParentheses++;
        else if(h == ")")
            numberOfRightParentheses++;
    }

    // only if number of parentheses is equal we can do conversion
    if(numberOfLeftParentheses == numberOfRightParentheses){
        for(auto h : expression){
            if(h == "+" || h == "-" || h == "*" || h == "/" || h == "%"){
                while(!s.empty() && this->getPriorityOfOperator(s.getTop()) >= this->getPriorityOfOperator(h)){
                    result += s.getTop() + " ";
                    s.pop();
                }
                s.push(h);
            } else if(h == "("){
                s.push(h);
            } else if(h == ")"){
                string last = s.getTop();
                s.pop();
                while(last != "("){
                    if(last != "("){
                        result += last + " ";
                    }
                    last = s.getTop();
                    s.pop();
                }
            } else {
                result += h + " ";
            }
        }

        while(!s.empty()){
            result += s.getTop() + " ";
            s.pop();
        }
    }

    // remove extra spaces from result
    this->removeSpaces(result);
    return result;
}

/// Method to remove white spaces from input string
/// \param str
/// \return string
string Expression::getStringWithoutWhiteSpaces(const string &str){
    string result = "";
    for(int i = 0; i < str.length(); i++)
        if(str[i] != '\n' && str[i] != '\r' && str[i] != '\t' && str[i] != '\b' && str[i] != '\v' && str[i] != '\0')
            result += str[i];

    return result;
}

/// Method which read file and parse it, after that this method call saveToFile method
/// \param fileName
/// \return bool
bool Expression::readFromFile(const string &fileName){
    ifstream file(fileName);
    string cycleVariable = "";
    string cycleValueFrom = "";
    string cycleValueTo = "";
    string variable = "";

    if(file){
        string str;
        while(getline(file, str)){
            size_t numberOfAssignmentSymbols = count(str.begin(), str.end(), '=');
            size_t numberOfCycleSymbols = count(str.begin(), str.end(), '>');

            // if we have some Assignment symbol in string, we know that we can assign variable with some value
            if(numberOfAssignmentSymbols > 0){
                if(numberOfAssignmentSymbols == 1){
                    string value;
                    int i = 0;
                    while(str[i] != '='){
                        variable += str[i];
                        i++;
                    }
                    i++;

                    while(i != str.length()){
                        value += str[i];
                        i++;
                    }
                    this->assignVariable(variable, value);
                } else {
                    throw ExpressionError("Too many Assignment Symbols in expression");
                }
            // if we have some Cycle symbols in string, we know that we can do for cycle
            } else if(numberOfCycleSymbols > 0){
                if(numberOfCycleSymbols == 2){
                    cycleVariable = "";
                    cycleValueFrom = "";
                    cycleValueTo = "";

                    int i = 0;
                    while(str[i] != '>'){
                        cycleVariable += str[i];
                        i++;
                    }
                    i++;
                    while(str[i] != '>'){
                        cycleValueFrom += str[i];
                        i++;
                    }
                    i++;
                    while(i != str.length()){
                        cycleValueTo += str[i];
                        i++;
                    }
                } else {
                    throw ExpressionError("Too many Assignment Symbols in expression");
                }
            } else {
                if(cycleVariable != "" && cycleValueFrom != "" && cycleValueTo != ""){
                    if(this->isNumber(cycleValueFrom) && this->isNumber(cycleValueTo)){
                        for(int i = stoi(cycleValueFrom); i < stoi(cycleValueTo); i++){
                            string expression = regex_replace(str, regex(cycleVariable), to_string(i));
                            int result = this->compute(this->getStringWithoutWhiteSpaces(expression));
                            resultOfExpressions.insert(pair<string,int>(expression,result));
                        }
                    } else {
                        throw ExpressionError("One or more values in cycle are not numbers");
                    }
                } else {
                    int result = this->compute(this->getStringWithoutWhiteSpaces(str));
                    resultOfExpressions.insert(pair<string,int>(str,result));
                }
            }
        }

        this->saveToFile("resultFrom" + fileName);
        return true;
    }

    return false;
}

/// Method save to file expressions from resultOfExpressions map
/// \param fileName
/// \return bool
bool Expression::saveToFile(const string &fileName) {
    ofstream file(fileName);

    //if map of expressions is empty, we don't want write to file
    if(resultOfExpressions.size() == 0)
        return false;

    if (file.is_open()){
        for(auto h: resultOfExpressions)
            file << h.first << " = " << h.second << endl;
        return true;
    }

    return false;
};

/// This method is used especially for testing
/// checks if we have correct expressions and results in file on specific indexes
/// \param fileName
/// \param indexOfLine
/// \return string
string Expression::getNthLineFromFile(const string &fileName, int indexOfLine){
    ifstream file(fileName);
    string result = "";
    int i = 0;

    if(file){
        string str;
        while(getline(file, str)){
            if(indexOfLine == i)
                result = str;
            i++;
        }
    }

    if(indexOfLine > i)
        throw ExpressionError("Bad index of line");

    return result;
}