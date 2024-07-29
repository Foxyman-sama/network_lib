#include <gmock/gmock.h>
#include <gtest/gtest.h>

int main() {
  testing::InitGoogleTest();
  testing::InitGoogleMock();
  return RUN_ALL_TESTS();
}
