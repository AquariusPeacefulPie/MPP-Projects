#include <gtest/gtest.h>

#include "Option.h"
#include "Parser.h"




TEST(isValid, avoir) {
op:: Parser parser;

char *fakeArgv[6];
int fakeArgc = 6;
fakeArgv[0] = "command";
fakeArgv[1] = "--option";
fakeArgv[2] = "bar";
fakeArgv[3] = "-a";
fakeArgv[4] = "pos1";
fakeArgv[5] = "pos2";



parser("option").hasValue().setDefaultValue("foo").setMandatory();
parser("alias").addAlias("a");
std::cout << parser("option").getValue() << std::endl;
parser.printHelp();
parser.parseCommandLine(fakeArgc , fakeArgv);
std::cout << "nb ArgumentPositional : " << parser.getPositionalArgumentCount() << std::endl;
std::cout << parser("option").getValue() << std::endl;
EXPECT_EQ(parser.getPositionalArgumentCount(),2);

}



int main(int argc, char* argv[]) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
