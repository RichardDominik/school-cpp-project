// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "main.h"

using namespace std;
using namespace ::testing;

TEST_F(Test, citanieSuboruZle) {
    Expression e;
    ASSERT_FALSE(e.readFromFile("no.txt"));
}

TEST_F(Test, citanieSuboruUspesne) {
    Expression e;
    ASSERT_TRUE(e.readFromFile("vyrazy.txt"));
}

TEST_F(Test, citanieSuboruSPremennouUspesne) {
    Expression e;
    ASSERT_TRUE(e.readFromFile("vyrazySPremennou.txt"));
}

TEST_F(Test, citanieSuboruSCyklomUspesne) {
    Expression e;
    ASSERT_TRUE(e.readFromFile("vyrazySCyklom.txt"));
    ASSERT_EQ("3 + 3 - 1 = 5", e.getNthLineFromFile("resultFromvyrazySCyklom.txt", 0));
}

TEST_F(Test, citanieSuboruDalsieVyrazyUspesne) {
    Expression e;
    ASSERT_TRUE(e.readFromFile("dalsieVyrazy.txt"));
    ASSERT_EQ("3 + x + 2 = 12", e.getNthLineFromFile("resultFromdalsieVyrazy.txt", 0));
    ASSERT_EQ("518 - 3 = 515", e.getNthLineFromFile("resultFromdalsieVyrazy.txt", 20));
    ASSERT_EQ("541 - 3 = 538", e.getNthLineFromFile("resultFromdalsieVyrazy.txt", 43));
    ASSERT_EQ("776 - 3 = 773", e.getNthLineFromFile("resultFromdalsieVyrazy.txt", 278));
    ASSERT_EQ("799 - 3 = 796", e.getNthLineFromFile("resultFromdalsieVyrazy.txt", 301));
}

TEST_F(Test, citanieDalsiehoSuboruZle) {
    Expression e;
    ASSERT_FALSE(e.readFromFile("n23o.txt"));
}

