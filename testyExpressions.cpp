#include <iostream>
#include "gtest/gtest.h"

#include "main.h"

using namespace std;
using namespace ::testing;

TEST_F(Test, konvertovanieNaIntUspesne) {
    Expression e;
    ASSERT_EQ(true, e.isNumber("345"));
}

TEST_F(Test, konvertovanieNaIntNeuspesne) {
    Expression e;
    ASSERT_EQ(false, e.isNumber("wed"));
}

TEST_F(Test, zistenieCiZnakJeOperatorUspesne) {
    Expression e;
    ASSERT_EQ(true, e.isOperator("%"));
}

TEST_F(Test, zistenieCiZnakJeOperatorNeuspesne) {
    Expression e;
    ASSERT_EQ(false, e.isOperator("."));
}

TEST_F(Test, testInfixToPostfix1) {
    Expression e;
    ASSERT_EQ("2 44 a3 222 * + 1 + pocet / +", e.infixToPostfix("2+(44+a3*222+1)/pocet"));
}

TEST_F(Test, testInfixToPostfix2) {
    Expression e;
    ASSERT_EQ("+ * / % -", e.infixToPostfix("+-*/%"));
}

TEST_F(Test, testComputePrefix) {
    Expression e;
    ASSERT_EQ(5, e.computePrefix("/ 5 1"));
}

TEST_F(Test, testComputePrefix2) {
    Expression e;
    ASSERT_EQ(7, e.compute("+ 5 2"));
}

TEST_F(Test, testComputePrefix3) {
    Expression e;
    ASSERT_EQ(8, e.compute("- + 8 / 6 3 2"));
}

TEST_F(Test, testComputePrefix4) {
    Expression e;
    ASSERT_EQ(25, e.compute("- + 7 * 4 5 + 2 0"));
}

TEST_F(Test, testComputePrefix4sPremennou) {
    Expression e;
    e.assignVariable("x", "7");

    ASSERT_EQ(25, e.compute("- + x * 4 5 + 2 0"));
}

TEST_F(Test, testComputePrefix4ibaSPremennymi) {
    Expression e;
    e.assignVariable("x", "7");
    e.assignVariable("y", "4");
    e.assignVariable("z", "5");
    e.assignVariable("v", "2");
    e.assignVariable("w", "0");

    ASSERT_EQ(25, e.compute("- + x * y z + v w"));
}


TEST_F(Test, testComputePostfix) {
    Expression e;

    ASSERT_EQ(757, e.compute("100 200 + 2 / 5 * 7 +"));
}

TEST_F(Test, testComputeInfix) {
    Expression e;

    ASSERT_EQ(-796, e.compute("3 - 4 - 800  + 1  * (2 + 3)"));
}

TEST_F(Test, vyhodnotenieVyrazuSPremennou) {
    Expression e;
    e.assignVariable("x", "13");
    ASSERT_EQ(3, e.compute("x%5"));
    ASSERT_EQ(3, e.compute("x 5%"));
    ASSERT_EQ(3, e.compute("%x 5"));
}

TEST_F(Test, Vyraz){
    Expression e;
    e.assignVariable("velmiPeknaPremenna", "800");
    e.assignVariable("dalsiaPeknaPremenna", "3");

    ASSERT_EQ(99257, e.compute("dalsiaPeknaPremenna + 2 * (velmiPeknaPremenna - 23) % 2 * (2 * 9 + 4) / dalsiaPeknaPremenna + 85 -21 + 49595 * 2"));
}

TEST_F(Test, chybaVoVyraze) {
    Expression e;
    e.assignVariable("x", "13");
    string message;
    try {
        ASSERT_EQ(3, e.compute("x 5"));
    }
    catch (ExpressionError(e)) {
        message = e.getMessage();
    }
    ASSERT_EQ("Error in expression", message);
}

TEST_F(Test, chybaDelenieNulou) {
    Expression e;
    string message;
    try {
        ASSERT_EQ(1, e.compute("5 0 /"));
    }
    catch (ExpressionError(e)) {
        message = e.getMessage();
    }
    ASSERT_EQ("Division by Zero", message);
}


