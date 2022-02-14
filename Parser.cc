#include "Parser.h"

#include <algorithm>
#include <stdexcept>
//RAjouter verif tiret avec plein de lettre
namespace op {
  void Parser::parseCommandLine(int argc, const char* const argv[]) {
    std::vector<std::string> PositionalArgumentTemp;
    std::string name;
    op::Option static * lastOption;
    // bool expectedValue = false;
    bool currentIsOption = false;
    bool lastIsOption = false;
    bool findTheOption = false;

    std::string previousIsOption = ""; 
    //On skip le premier elements qui est la command
    for(auto i = 1 ; i < argc ; i++){
      if(lastIsOption) {
        std::cout<< "Si celui d'avant est  une option : "<<lastOption->getNames().front() << "\n" ;
      }

      name = argv[i];
      if(name[0] == '-'){
        name = name.substr(1);
        std::cout << "test1 :" << name << "\n" ;
        currentIsOption = true;
      }else{
        currentIsOption = false;
      }

      if(!currentIsOption){
          std::cout << "Pas une option \n";
        if( lastIsOption && (*lastOption).expectValue()){
                  std::cout << "debug \n";
           *lastOption=name;
        }else{
          PositionalArgumentTemp.push_back(name);
        }


         lastIsOption = false;
      //CURRENT EST UNE OPTION
      }else{

        // if(isTheEnd){
        //   PositionalArgumentTemp.clear();
        //   isTheEnd = false;
        // }

        if( lastIsOption  ){
          if((lastOption->getValue() == "") && lastOption->expectValue()){
            throw std::runtime_error("Cette option attend une valeur");
          }
          // std::cout<< "alors lal allalal \n" ;
          //PROBLEME L'OPTION PRECEDENTE N'A PAS DE VALEUR
        }

        
          if(name[0] == '-'){
            // if(name.size() == 1){
            //   throw std::runtime_error("Le nom de l'option est vide");
            // }
            name = name.substr(1);
          //POUR LES ALIAS
          }

          if(name.size() == 0){
            throw std::runtime_error("Le nom de l'option est vide");
          }          

        for(auto &option : options){
          if(option == name){
            option.parsed();
            findTheOption = true;
            lastOption = &option;
            std::cout<< "yoyooyoy : "<<lastOption->getNames().front() << "\n" ;
            lastIsOption = true;
          }
        }
        if(!findTheOption){
          throw std::runtime_error("Cette option n'existe pas ");
        }
        findTheOption = false;

      }


    }
    this->PositionalArgument = PositionalArgumentTemp;
    for(auto option : options){
      if(option.isMandatory() && (option) ){
        throw std::runtime_error("option obligatoire non mise");
      }
    }    
    //Verifier si il y a des options obligatoire non lue

  }

  void Parser::printHelp(std::ostream& stream) const {
    // TODO: not yet implemented
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
