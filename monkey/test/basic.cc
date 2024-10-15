// basic_test.cpp
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);

  // Set GoogleTest to stop on first failure
  GTEST_FLAG_SET(break_on_failure, true);

  // Run all tests
  return RUN_ALL_TESTS();
}
