#include <gtest/gtest.h>

#include "Tuple.h"

TEST(constructor,construction){
  t::Tuple<int,double> test;
}



int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
