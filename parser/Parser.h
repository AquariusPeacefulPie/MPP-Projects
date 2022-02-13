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
    //Attributes
    std::vector<op::Option> m_options;
    std::vector<std::string> m_positionalArguments;

    //Methods
    bool isOption(const char* const &arg);
    bool isPositionalArgument(const char* const &arg);
  };
}

#endif // OP_PARSER_H_
