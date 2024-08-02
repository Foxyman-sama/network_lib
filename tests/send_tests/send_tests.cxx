#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace testing;

int main() {
  InitGoogleTest();
  InitGoogleMock();
  return RUN_ALL_TESTS();
}
