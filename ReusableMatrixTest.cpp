#include <gtest/gtest.h>
#include "ReusableMatrix.hpp"

TEST(Reusable, Test1) {
    ReusableMatrix.reserve(5,{5,3});
    auto x = ReusableMatrix.make({5,3});
    {auto y = ReusableMatrix.make({5,3});}
    size_t available = ReusableMatrix.countFree({5,3});
    EXPECT_EQ(available, 4) << "Available count does not match";
}
