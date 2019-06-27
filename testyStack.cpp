// Copyright 2005, Google Inc.
// All rights reserved.

#include <iostream>
#include "gtest/gtest.h"

#include "main.h"

using namespace std;
using namespace ::testing;

TEST_F(Test, StackInt) {
	Stack<int> s;
	s.push(10);
	s.push(20);
	s.push(30);
	ASSERT_EQ(30, s.getTop());
    s.pop();
	ASSERT_EQ(false, s.empty());
	s.pop();
	s.pop();
	ASSERT_EQ(true, s.empty());
}

TEST_F(Test, StackString) {
	Stack<string> s;
	s.push("10");
	s.push("20");
	s.push("30");
	ASSERT_EQ("30", s.getTop());
	s.pop();
	ASSERT_EQ(false, s.empty());
	s.pop();
	s.pop();
	ASSERT_EQ(true, s.empty());
}





