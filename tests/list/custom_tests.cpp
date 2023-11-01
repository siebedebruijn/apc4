#include <gtest/gtest.h>

#include "list.h"

TEST(custom, always_pass) {
    ASSERT_TRUE(1 + 1 == 2) << "This test must always pass";
}

// Place your custom tests here
// add your own custom tests here if needed

TEST(custom, empty_size) {
    saxion::list<int> lst{};
    ASSERT_TRUE(lst.empty()) << "This list should be empty";
}
