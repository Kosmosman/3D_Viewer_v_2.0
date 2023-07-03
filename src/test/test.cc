#include <gtest/gtest.h>

#include <string>

#include "../Model/parcer/parcer.h"

TEST(ParcerTest, GetVertexesTest) {
  // std::string filename = "test.obj";
  // s21::Parcer parcer_(filename);
  // EXPECT_EQ(parcer_.GetVertexes().size(), 24);

  std::string filename = "./test/cube.obj";
  s21::Parcer p(filename);
  std::cout << "Size = " << p.GetVertexes().size() << std::endl;
  EXPECT_EQ(p.GetVertexes().size(), 24);
}

TEST(ParcerTest, GetFacetsTest) {
  std::string filename = "./test/cube.obj";
  s21::Parcer parcer_(filename);
  EXPECT_EQ(parcer_.GetFacets().size(), 48);
}

TEST(ParcerTest, GetMaxCoordinate) {
  std::string filename = "./test/cube.obj";
  s21::Parcer parcer_(filename);
  EXPECT_EQ(parcer_.GetMaxCoordinate(), 1);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
