#include "Option.h"

#include <stdexcept>

namespace op {
  Option::Option(const std::string& name) {
      this->names.push_back(name);
      this->value = "";
      this->expectedValue = false;
      this->mandatory = false;
      this->read = false;
  }

  const std::vector<std::string>& Option::getNames() const {
      return this->names;
  }

  const std::string& Option::getValue() const {
      return this->value;
  }

  bool Option::expectValue() const {
    return this->expectedValue;
  }

  Option& Option::setDefaultValue(const std::string& value) {
    if(Option::expectValue()){
      this->value = value;
    }else{
      throw std::runtime_error("No value expected");
    }
    return *this;
  }

  Option& Option::hasValue() {
    this->expectedValue = true;
    return *this;
  }

  Option& Option::addAlias(const std::string& alias) {
    bool contain = false;
    for(auto &name : this->getNames()){
      if(name == alias){
        contain = true;
      }
    }
    if(!contain){
      this->names.push_back(alias);
    }
    return *this;
  }

  Option& Option::setMandatory() {
    this->mandatory = true;
    return *this;
  }

  bool Option::isMandatory() const {
    return this->mandatory;
  }

  void Option::parsed(){
    this->read = true;
  }

  bool Option::operator==(const std::string& arg) const {
    for(auto &name : this->getNames()){
      if(name == arg){
        return true;
      }
    }
    return false;
  }

  bool Option::operator!=(const std::string& arg) const {
    return (!this->operator==(arg));
  }

  Option& Option::operator=(const std::string& value) {
    this->value = value;
    return *this;
  }

  Option::operator bool() const {
    return this->read;
  }
}
