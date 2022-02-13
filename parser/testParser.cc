#include <gtest/gtest.h>

#include "Option.h"
#include "Parser.h"



TEST(test,basic){
  op::Parser parser;
  parser("option").hasValue().setDefaultValue("foo");
  parser("option").addAlias("o");
  parser("option2").hasValue().setDefaultValue("foo2");

  parser("option3").hasValue().setDefaultValue("foo3");
  parser("option2").addAlias("o2");

  parser.printHelp();

}


int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}