#include <gtest/gtest.h>

#include "Option.h"
#include "Parser.h"




TEST(isValid, avoir) {
  op::Parser parser;

  char *fakeArgv[6];
  int fakeArgc = 6;
  fakeArgv[0] = "command";
  fakeArgv[1] = "--option";
  fakeArgv[2] = "bar";
  fakeArgv[3] = "-a";
  fakeArgv[4] = "pos1";
  fakeArgv[5] = "pos2";



  parser("option").hasValue().setDefaultValue("foo");
  parser("alias").addAlias("a");
  std::cout<<parser("option").getValue()<<std::endl;
  parser.printHelp();
  parser.parseCommandLine(fakeArgc , fakeArgv);
  std::cout<<"nb ArgumentPositional : "<<parser.getPositionalArgumentCount()<<std::endl;
  std::cout<<parser("option").getValue()<<std::endl;
  EXPECT_EQ(parser.getPositionalArgumentCount(),2);
}

TEST(parseCommandLine,optionMandatoryIsHere){
  op::Parser parser;

  parser("option").setMandatory();

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "--option";

  EXPECT_NO_THROW(parser.parseCommandLine(testArgc,testArgv));
}

TEST(parseCommandLine,optionMandatoryIsNotHere){
  op::Parser parser;

  parser("option").setMandatory();

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "--alias";

  EXPECT_THROW(parser.parseCommandLine(testArgc,testArgv),std::runtime_error);
}


TEST(parseCommandLine,optionExpectValueHasValue){
  op::Parser parser;

  parser("option").hasValue();

  char *testArgv[3];
  int testArgc = 3;
  testArgv[0] = "command";
  testArgv[1] = "--option";
  testArgv[2] = "foo";

  EXPECT_NO_THROW(parser.parseCommandLine(testArgc,testArgv));
}


TEST(parseCommandLine,optionExpectValueHasNoValue){
  op::Parser parser;

  parser("option").hasValue();

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "--option";

  EXPECT_THROW(parser.parseCommandLine(testArgc,testArgv),std::runtime_error);
}

//A retirer si incorrect
TEST(parseCommandLine,emptyInsteadExpectedValue){
  op::Parser parser;

  parser("option").hasValue();

  char *testArgv[3];
  int testArgc = 3;
  testArgv[0] = "command";
  testArgv[1] = "--option";
  testArgv[2] = "";

  EXPECT_THROW(parser.parseCommandLine(testArgc,testArgv),std::runtime_error);
}


TEST(parseCommandLine,optionEmptyName){
  op::Parser parser;

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "";

  EXPECT_THROW(parser.parseCommandLine(testArgc,testArgv),std::runtime_error);
}

/* Test the writing of the option names */

TEST(parseCommandLine,optionNameOneDashCorrect){
  op::Parser parser;

  parser("o");

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "-o";

  EXPECT_NO_THROW(parser.parseCommandLine(testArgc,testArgv));
}

TEST(parseCommandLine,optionNameOneDashIncorrect){
  op::Parser parser;

  parser("oo");

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "-oo";

  EXPECT_THROW(parser.parseCommandLine(testArgc,testArgv),std::runtime_error);
}

TEST(parseCommandLine,optionNameDoubleDashCorrect){
  op::Parser parser;

  parser("option");

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "--option";

  parser.parseCommandLine(testArgc,testArgv);
}

TEST(parseCommandLine,optionNameDoubleDashIncorrect){
  op::Parser parser;

  parser("o");

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "--o";

  EXPECT_THROW(parser.parseCommandLine(testArgc,testArgv),std::runtime_error);
}

/* Test the position of both options and positional arguments */

TEST(parseCommandLine,positionalArgumentsAtTheEnd){
  op::Parser parser;

  parser("f");

  char *testArgv[4];
  int testArgc = 4;
  testArgv[0] = "cp";
  testArgv[1] = "-f";
  testArgv[2] = "source";
  testArgv[3] = "dest";

  EXPECT_NO_THROW(parser.parseCommandLine(testArgc,testArgv));
}

TEST(parseCommandLine,positionalArgumentsFirst){
  op::Parser parser;

  parser("f");

  char *testArgv[4];
  int testArgc = 4;
  testArgv[0] = "cp";
  testArgv[1] = "source";
  testArgv[2] = "dest";
  testArgv[3] = "-f";

  EXPECT_NO_THROW(parser.parseCommandLine(testArgc,testArgv));
}

TEST(parseCommandLine,positionalArgumentsBetweenOptions){
  op::Parser parser;

  parser("f");
  parser("n");

  char *testArgv[5];
  int testArgc = 5;
  testArgv[0] = "cp";
  testArgv[1] = "-n";
  testArgv[2] = "source";
  testArgv[3] = "dest";
  testArgv[4] = "-f";

  EXPECT_NO_THROW(parser.parseCommandLine(testArgc,testArgv));
}

TEST(parseCommandLine,sameOptionMultipleTimes){
  op::Parser parser;

  parser("option");

  char *testArgv[3];
  int testArgc = 3;
  testArgv[0] = "cp";
  testArgv[1] = "--option";
  testArgv[2] = "--option";

  EXPECT_NO_THROW(parser.parseCommandLine(testArgc,testArgv));
}

TEST(parseCommandLine,sameOptionMultipleTimesSavesLastValue){
  op::Parser parser;

  parser("option").hasValue();

  char *testArgv[5];
  int testArgc = 5;
  testArgv[0] = "command";
  testArgv[1] = "--option";
  testArgv[2] = "foo";
  testArgv[3] = "--option";
  testArgv[4] = "foo2";

  EXPECT_NO_THROW(parser.parseCommandLine(testArgc,testArgv));
  EXPECT_EQ(parser("option").getValue(),"foo2");
}

TEST(parseCommandLine,sameOptionMultipleTimesDifferentPlacesSavesLastValue){
  op::Parser parser;

  parser("option").hasValue();
  parser("option2");


  char *testArgv[7];
  int testArgc = 7;
  testArgv[0] = "command";
  testArgv[1] = "--option";
  testArgv[2] = "foo";
  testArgv[3] = "--option2";
  testArgv[4] = "pos1";
  testArgv[5] = "--option";
  testArgv[6] = "foo2";

  EXPECT_NO_THROW(parser.parseCommandLine(testArgc,testArgv));
  EXPECT_EQ(parser("option").getValue(),"foo2");
}

TEST(parseCommandLine,correctNumberPositionalArguments){
  op::Parser parser;

  parser("option").hasValue();
  parser("a");
  parser("option");


  char *testArgv[6];
  int testArgc = 6;
  testArgv[0] = "cp";
  testArgv[1] = "--option";
  testArgv[2] = "bar";
  testArgv[3] = "-a";
  testArgv[4] = "pos1";
  testArgv[5] = "pos2";

  EXPECT_NO_THROW(parser.parseCommandLine(testArgc,testArgv));
  EXPECT_EQ(parser.getPositionalArgumentCount(),2);
}

TEST(parseCommandLine,helpCallCommand){
  op::Parser parser;

  parser("help");

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "--help";


  EXPECT_THROW(parser.parseCommandLine(testArgc,testArgv),std::runtime_error);
}

TEST(parseCommandLine,helpCallCommandAlias){
  op::Parser parser;

  parser("h");

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "-h";
  
  EXPECT_THROW(parser.parseCommandLine(testArgc,testArgv),std::runtime_error);
}

TEST(parseCommandLine,helpCallExpectExit){
  op::Parser parser;

  parser("help");

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "--help";
  
  EXPECT_EXIT(parser.parseCommandLine(testArgc,testArgv),::testing::ExitedWithCode(EXIT_FAILURE),"");
}

TEST(parseCommandLine,optionUndefinedOneDash){
  op::Parser parser;

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "-u";
  
  EXPECT_THROW(parser.parseCommandLine(testArgc,testArgv),std::runtime_error);
}

TEST(parseCommandLine,optionUndefinedDoubleDash){
  op::Parser parser;

  char *testArgv[2];
  int testArgc = 2;
  testArgv[0] = "command";
  testArgv[1] = "--undefined";
  
  EXPECT_THROW(parser.parseCommandLine(testArgc,testArgv),std::runtime_error);
}




int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
