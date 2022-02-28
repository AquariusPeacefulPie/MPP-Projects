#include "Parser.h"

#include <algorithm>
#include <stdexcept>
//RAjouter verif tiret avec plein de lettre
namespace op {
  void Parser::parseCommandLine(int argc, const char* const argv[]) {
    // std::vector<std::string> PositionalArgumentTemp;
    std::string name;
    op::Option static * lastOption;
    // bool expectedValue = false;
    bool currentIsOption = false;
    bool lastIsOption = false;
    bool findTheOption = false;

    std::string previousIsOption = ""; 
    //On skip le premier elements qui est la command
    for(auto i = 1 ; i < argc ; i++){


      name = argv[i];


      if(lastIsOption && (*lastOption).expectValue()){
        *lastOption = name;
        lastIsOption = false;
      }else{

        if(name[0] == '-') {
          name = name.substr(1);
          if(name[0] == '-'){
            name = name.substr(1);          
          }
          if(name == "help" || name == "h"){
            printHelp(std::cout);
          }
          if(name.size() == 0){
            throw std::runtime_error("Le nom de l'option est vide");
          }
          for(auto &option : options){
            if(option == name){
              if( (i == argc - 1) && option.expectValue() && option.getValue() == "" ){
                throw std::runtime_error("Cette option attend une valeur");
              }              
              option.parsed();
              findTheOption = true;
              lastOption = &option;
              lastIsOption = true;
            }
          }
          if(!findTheOption){
            throw std::runtime_error("Cette option n'existe pas ");
          }
          findTheOption = false;
        }else{
          this->PositionalArgument.push_back(name);
        }


      }


      // if(!currentIsOption){
      //     std::cout << "Pas une option \n";
      //   if( lastIsOption && (*lastOption).expectValue()){
      //             std::cout << "debug \n";
      //      *lastOption=name;
      //   }else{
      //     PositionalArgumentTemp.push_back(name);
      //   }


      //    lastIsOption = false;
      // //CURRENT EST UNE OPTION
      // }else{

      //   // if(isTheEnd){
      //   //   PositionalArgumentTemp.clear();
      //   //   isTheEnd = false;
      //   // }

      //   if( lastIsOption  ){
      //     if((lastOption->getValue() == "") && lastOption->expectValue()){
      //       throw std::runtime_error("Cette option attend une valeur");
      //     }
      //     // std::cout<< "alors lal allalal \n" ;
      //     //PROBLEME L'OPTION PRECEDENTE N'A PAS DE VALEUR
      //   }

        
      //     if(name[0] == '-'){
      //       // if(name.size() == 1){
      //       //   throw std::runtime_error("Le nom de l'option est vide");
      //       // }
      //       name = name.substr(1);
      //     //POUR LES ALIAS
      //     }

      //     if(name.size() == 0){
      //       throw std::runtime_error("Le nom de l'option est vide");
      //     }          

      //   for(auto &option : options){
      //     if(option == name){
      //       option.parsed();
      //       findTheOption = true;
      //       lastOption = &option;
      //       std::cout<< "yoyooyoy : "<<lastOption->getNames().front() << "\n" ;
      //       lastIsOption = true;
      //     }
      //   }
      //   if(!findTheOption){
      //     throw std::runtime_error("Cette option n'existe pas ");
      //   }
      //   findTheOption = false;

      // }


    }
    // this->PositionalArgument = PositionalArgumentTemp;
    for(auto option : options){
      if(option.isMandatory() && !(option) ){
        throw std::runtime_error("option obligatoire non mise");
      }
    }    
    //Verifier si il y a des options obligatoire non lue

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
