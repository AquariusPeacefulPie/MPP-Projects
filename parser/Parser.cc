#include "Parser.h"

#include <algorithm>
#include <stdexcept>

#include <cstring>
#include <string>
#include <vector>

namespace op {

  //Implementation of the private methods
  bool Parser::isOption(const char* const &arg){
    std::string argToStr(arg);
    if(strlen(arg)>=3){
      if(arg[0]=='-'&&arg[1]=='-'){
        std::string argToStrTruncated(argToStr.substr(2,argToStr.size()-2));
        //Check if the parser contains the option
        if(std::find(this->m_options.begin(),this->m_options.end(),argToStrTruncated)!=this->m_options.end()){
          return true;
        }
        return false;
      }
      return false;      
    }
    else{
      if(arg[0]=='-'){
        std::string argToStrTruncated(argToStr.substr(1,argToStr.size()-1));
        //Check if the parser contains the option
        if(std::find(this->m_options.begin(),this->m_options.end(),argToStrTruncated)!=this->m_options.end()){
          return true;
        }
        return false;
      }
      return false;
    }
  }

  bool Parser::isPositionalArgument(const char* const &arg){
    std::string argToStr(arg);
    if(std::find(this->m_positionalArguments.begin(),this->m_positionalArguments.end(),argToStr)!=this->m_positionalArguments.end()){
      return true;
    }
    return false;
  }

  void Parser::parseCommandLine(int argc, const char* const argv[]) {
    // TODO: not yet implemented
    for(size_t i = 1; i<argc; ++i){
      if(this->isOption(argv[i])){
        op::Option option = this->operator()(std::string(argv[i]));
      }
      else{
        if(this->isPositionalArgument(argv[i])){
          this->m_positionalArguments.push_back(std::string(argv[i]));
        }
        else{

        }
      }
    }
  }

  void Parser::printHelp(std::ostream& stream) const {
    stream<<"Usage :"<<std::endl;
    for(auto option : this->m_options){
      std::vector<std::string> names = option.getNames();
      bool unique = true;
      stream<<"\t";
      for(auto name : names){
        if(name.size()==1){
          if(!unique){
            stream<<"|";
          }
          stream<<"-"<<name;
        }
        else{
          if(!unique){
            stream<<"|";
          }
          stream<<"--"<<name;
        }
        unique = false;
      }
      stream<<std::endl;
    }
    stream<<"\t--help|-h"<<std::endl;
  }

  std::size_t Parser::getPositionalArgumentCount() const {
    // TODO: not yet implemented
    return this->m_positionalArguments.size();
  }

  Option& Parser::operator()(const std::string& name) {
    for(auto &it : this->m_options){
      if(it == name){
        return it;
      }
    }
    this->m_options.push_back(Option(name));
    return this->m_options.back();
  }

  const std::string& Parser::operator[](std::size_t i) const {
    if(this->getPositionalArgumentCount()<=i){
      throw std::out_of_range("Argument out of range");
    }
    return this->m_positionalArguments.at(i);
  }
}
