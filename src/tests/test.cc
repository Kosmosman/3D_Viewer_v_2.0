#include <gtest/gtest.h>

#include <string>
#include <iostream>

#include "../Model/parcer/parcer.h"
#include "../Model/basic_model/model.h"
#include "../Model/affine_transformations/affinis.h"

TEST(ParcerTest, BasicTest) {
  std::string filename = "/opt/goinfre/joaquind/CPP4_3DViewer_v2.0-1/src/obj/cube.obj";
  s21::Parcer parcer_(filename);
    EXPECT_TRUE(parcer_.IsValid());
  EXPECT_EQ(parcer_.GetVertexes().size() / 3, 24);
  EXPECT_EQ(parcer_.GetCountOfFacets(), 12);
  EXPECT_NEAR(parcer_.GetMaxCoordinate(), 0.5, 0.0000001);
}

TEST(ParcerTest, WrongTestOne) {
  std::string filename = "/opt/goinfre/joaquind/CPP4_3DViewer_v2.0-1/src/obj/pyramid.obj";
  s21::Parcer parcer_(filename);
    EXPECT_FALSE(parcer_.IsValid());
}

TEST(ParcerTest, WrongTestTwo) {
    std::string filename = "/opt/goinfre/joaquind/CPP4_3DViewer_v2.0-1/src/obj/wrong.obj";
    s21::Parcer parcer_(filename);
    EXPECT_FALSE(parcer_.IsValid());
}

TEST(AffinesTest, MoveCoordX) {
    std::string filename = "/opt/goinfre/joaquind/CPP4_3DViewer_v2.0-1/src/tests/test_obj/1.obj";
    s21::Model mod(filename);
    s21::AffinisOperation<s21::MoveX> op;
    double eq[9]{2, 0, 0, 1, 1, 0, 1, 0, 1};
    double* ptr = eq;
    op.MakeCalculate(mod.GetVertexes(), 1);
    EXPECT_TRUE(mod.IsValid());
    for (auto it: mod.GetVertexes()) {
        EXPECT_NEAR(*ptr++, it, 0.0000001);
    }
}

TEST(AffinesTest, MoveCoordY) {
    std::string filename = "/opt/goinfre/joaquind/CPP4_3DViewer_v2.0-1/src/tests/test_obj/1.obj";
    s21::Model mod(filename);
    s21::AffinisOperation<s21::MoveY> op;
    double eq[9]{1, 1, 0, 0, 2, 0, 0, 1, 1};
    double* ptr = eq;
    op.MakeCalculate(mod.GetVertexes(), 1);
    EXPECT_TRUE(mod.IsValid());
    for (auto it: mod.GetVertexes()) {
    EXPECT_NEAR(*ptr++, it, 0.0000001);
    }
}

TEST(AffinesTest, MoveCoordZ) {
    std::string filename = "/opt/goinfre/joaquind/CPP4_3DViewer_v2.0-1/src/tests/test_obj/1.obj";
    s21::Model mod(filename);
    s21::AffinisOperation<s21::MoveZ> op;
    double eq[9]{1, 0, 1, 0, 1, 1, 0, 0, 2};
    double* ptr = eq;
    op.MakeCalculate(mod.GetVertexes(), 1);
    EXPECT_TRUE(mod.IsValid());
    for (auto it: mod.GetVertexes()) {
    EXPECT_NEAR(*ptr++, it, 0.0000001);
    }
}

TEST(AffinesTest, RotateCoordX) {
    std::string filename = "/opt/goinfre/joaquind/CPP4_3DViewer_v2.0-1/src/tests/test_obj/2.obj";
    s21::Model mod(filename);
    s21::AffinisOperation<s21::RotateX> op;
    double eq[9]{1, 1, -1, 2, 2, -2, 3, 3, -3};
    double* ptr = eq;
    op.MakeCalculate(mod.GetVertexes(), 90);
    EXPECT_TRUE(mod.IsValid());
    for (auto it = mod.GetVertexes().begin(); it < mod.GetVertexes().end(); it += 3, ptr += 3) {
        EXPECT_NEAR(*ptr, *it, 0.0000001);
    }
    ptr = eq + 1;
    for (auto it = mod.GetVertexes().begin() + 1; it < mod.GetVertexes().end(); it += 3, ptr += 3) {
        EXPECT_NEAR(*ptr, *it, 0.0000001);
    }
    ptr = eq + 2;
    for (auto it = mod.GetVertexes().begin() + 2; it < mod.GetVertexes().end(); it += 3, ptr += 3) {
        EXPECT_NEAR(*ptr, *it, 0.0000001);
    }
}

TEST(AffinesTest, RotateCoordY) {
    std::string filename = "/opt/goinfre/joaquind/CPP4_3DViewer_v2.0-1/src/tests/test_obj/2.obj";
    s21::Model mod(filename);
    s21::AffinisOperation<s21::RotateY> op;
    double eq[9]{1, 1, -1, 2, 2, -2, 3, 3, -3};
    double* ptr = eq;
    op.MakeCalculate(mod.GetVertexes(), 90);
    EXPECT_TRUE(mod.IsValid());
    for (auto it = mod.GetVertexes().begin(); it < mod.GetVertexes().end(); it += 3, ptr += 3) {
        EXPECT_NEAR(*ptr, *it, 0.0000001);
    }
    ptr = eq + 1;
    for (auto it = mod.GetVertexes().begin() + 1; it < mod.GetVertexes().end(); it += 3, ptr += 3) {
        EXPECT_NEAR(*ptr, *it, 0.0000001);
    }
    ptr = eq + 2;
    for (auto it = mod.GetVertexes().begin() + 2; it < mod.GetVertexes().end(); it += 3, ptr += 3) {
        EXPECT_NEAR(*ptr, *it, 0.0000001);
    }
}

TEST(AffinesTest, RotateCoordZ) {
    std::string filename = "/opt/goinfre/joaquind/CPP4_3DViewer_v2.0-1/src/tests/test_obj/2.obj";
    s21::Model mod(filename);
    s21::AffinisOperation<s21::RotateZ> op;
    double eq[9]{-1, 1, 1, -2, 2, 2, -3, 3, 3};
    double* ptr = eq;
    op.MakeCalculate(mod.GetVertexes(), 90);
    EXPECT_TRUE(mod.IsValid());
    for (auto it = mod.GetVertexes().begin(); it < mod.GetVertexes().end(); it += 3, ptr += 3) {
        EXPECT_NEAR(*ptr, *it, 0.0000001);
    }
    ptr = eq + 1;
    for (auto it = mod.GetVertexes().begin() + 1; it < mod.GetVertexes().end(); it += 3, ptr += 3) {
        EXPECT_NEAR(*ptr, *it, 0.0000001);
    }
    ptr = eq + 2;
    for (auto it = mod.GetVertexes().begin() + 2; it < mod.GetVertexes().end(); it += 3, ptr += 3) {
        EXPECT_NEAR(*ptr, *it, 0.0000001);
    }
}

TEST(AffinesTest, Scaling) {
    std::string filename = "/opt/goinfre/joaquind/CPP4_3DViewer_v2.0-1/src/tests/test_obj/2.obj";
    s21::Model mod(filename);
    s21::AffinisOperation<s21::Scaling> op;
    double eq[9]{2, 2, 2, 4, 4, 4, 6, 6, 6};
    double* ptr = eq;
    op.MakeCalculate(mod.GetVertexes(), 2);
    EXPECT_TRUE(mod.IsValid());
    for (auto it: mod.GetVertexes()) {
        EXPECT_NEAR(*ptr++, it, 0.0000001);
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
