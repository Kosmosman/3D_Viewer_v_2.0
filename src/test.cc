#include <gtest/gtest.h>

#include <string>

#include "./Model/parcer/parcer.h"

TEST(ParcerTest, BasicTest) {
  std::string filename = "./obj/test.obj";
  s21::Parcer parcer_(filename);
  EXPECT_EQ(parcer_.GetVertexes().size() / 3, 8);
  EXPECT_EQ(parcer_.GetFacets().size(), 12);
  EXPECT_EQ(parcer_.GetMaxCoordinate(), 1);
}

TEST(ParcerTest, PyramidTest) {
  std::string filename = "./obj/pyramid.obj";
  s21::Parcer parcer_(filename);
  EXPECT_EQ(parcer_.GetVertexes().size() / 3, 5);
  EXPECT_EQ(parcer_.GetFacets().size(), 6);
  EXPECT_EQ(parcer_.GetMaxCoordinate(), 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
