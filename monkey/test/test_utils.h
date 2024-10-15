#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <gtest/gtest.h>

class BaseTest : public testing::Test {
protected:
    void SetUp() override {
        // Code that runs before each test in BasicTest and AdvancedTest.
    }

    void TearDown() override {
        // Code that runs after each test in BasicTest and AdvancedTest.
    }
};

class BasicTest : public BaseTest {
protected:
    void SetUp() override {
        BaseTest::SetUp();
        // Additional setup specific to basic tests
    }

    void TearDown() override {
        // Additional teardown specific to basic tests
        BaseTest::TearDown();
    }
};

class AdvancedTest : public BaseTest {
protected:
    void SetUp() override {
        BaseTest::SetUp();
        // Additional setup specific to advanced tests
    }

    void TearDown() override {
        // Additional teardown specific to advanced tests
        BaseTest::TearDown();
    }
};

#endif //TEST_UTILS_H
