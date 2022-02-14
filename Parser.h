#ifndef OP_PARSER_H_
#define OP_PARSER_H_

#include <iostream>
#include <vector>

#include "Option.h"

namespace op {
  class Parser {
  public:
    void parseCommandLine(int argc, const char* const argv[]);
    void printHelp(std::ostream& stream = std::cout) const;
    std::size_t getPositionalArgumentCount() const;

    Option& operator()(const std::string& name);
    const std::string& operator[](std::size_t i) const;
  private:
    //Private attributes
    std::vector<op::Option> options;
    std::vector<std::string> PositionalArgument;

    //Private methods
    static  void printOptionInformation(op::Option& option, std::ostream& stream);
  };
}

#endif // OP_PARSER_H_
