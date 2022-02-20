#include "Parser.h"
#include <algorithm>
#include <stdexcept>

namespace op {

  std::string Parser::checkOptionFormat(std::string optionName) {
    optionName = optionName.substr(1);
    if(optionName[0] == '-'){
      //Case option with two dot
      optionName = optionName.substr(1);
      if(optionName.size() == 1 ){
        throw std::runtime_error("Option with bad format");
      }          
    }else{
      //Case option with one dot
      if(optionName.size() != 1){
        throw std::runtime_error("Option with bad format");
      }
    }

    if(optionName.size() == 0){
      throw std::runtime_error("Empty option");
    }

    return optionName;
  }

  void Parser::parseCommandLine(int argc, const char* const argv[]) {
    std::string name;
    op::Option static * lastOption;
    bool lastIsOption = false;
    bool findTheOption = false;

    for(auto i = 1 ; i < argc ; i++){

      name = argv[i];
      if(name.size() == 0){
        throw std::runtime_error("Empty argument");
      }

      if(lastIsOption && (*lastOption).expectValue()){
        *lastOption = name;
        lastIsOption = false;
      }else{
        //Current argument of argv is an option
        if(name[0] == '-') {
          name = checkOptionFormat(name);
          if(name == "help" || name == "h"){
            printHelp(std::cout);
          }

          for(auto &option : options){
            if(option == name){
              if( (i == argc - 1) && option.expectValue() && option.getValue() == "" ){
                throw std::runtime_error("Option expects a value");
              }              
              option.parsed();
              findTheOption = true;
              lastOption = &option;
              lastIsOption = true;
            }
          }
          
          if(!findTheOption){
            throw std::runtime_error("Option doesn't exist");
          }
          findTheOption = false;
        }else{
          this->PositionalArgument.push_back(name);
        }
      }
    }
    for(auto option : options){
      if(option.isMandatory() && !(option) ){
        throw std::runtime_error("Mandatory option not present");
      }
    }    

  }

  void Parser::printOptionInformation(op::Option& option, std::ostream& stream){
    if(option.expectValue()){
      stream<<" value";
      std::string defaultValue = option.getValue();
      if(defaultValue!=""){
        stream<<" (default "<<defaultValue;
      }
    }
   
    if(option.isMandatory()){
      stream<<" MANDATORY";
    }
  }

  void Parser::printHelp(std::ostream& stream) const {
    stream<<"Usage :"<<std::endl;
    for(auto option : this->options){
      std::vector<std::string> names = option.getNames();
      bool unique = true;
      stream<<"\t";
      for(auto name : names){
        if(name.size()==1){
          if(!unique){
            stream<<"|";
          }
          stream<<"-"<<name;
          printOptionInformation(option,stream);
        }
        else{
          if(!unique){
            stream<<"|";
          }
          stream<<"--"<<name;
          printOptionInformation(option,stream);
        }
        unique = false;
      }
      stream<<std::endl;
    }
    stream<<"\t--help|-h"<<std::endl;
    exit(1);
  }

  std::size_t Parser::getPositionalArgumentCount() const {
    return this->PositionalArgument.size();
  }

  Option& Parser::operator()(const std::string& name) {
    for(auto &option : options){
      if(option == name){
        return option;
      }
    }
    
    this->options.push_back(Option(name));
    return this->options.back();
  }

  const std::string& Parser::operator[](std::size_t i) const {
    if(i < getPositionalArgumentCount()){
      return this->PositionalArgument.at(i);
    }
      throw std::out_of_range("The positional argument doesn't exist");

  }
}
