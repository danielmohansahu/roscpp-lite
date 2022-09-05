/* Unit test of the roscpp_lite API.
 *
 */

#include <gtest/gtest.h>
#include "roscpp_lite/subscriber.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);
}
