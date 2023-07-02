#include <gtest/gtest.h>

#include <string>

#include "../parcer/parcer.h"

TEST(ParcerTest, constructor_default_size) {
  std::string filename = "../../obj/test.obj";
  s21::Parcer parcer_(filename);
  EXPECT_EQ(parcer_.GetVertexes().size(), 8);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
