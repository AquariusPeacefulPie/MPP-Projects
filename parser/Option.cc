#include "Option.h"

#include <stdexcept>

namespace op {
  Option::Option(const std::string& name) {
    this->m_names.push_back(name);
  }

  const std::vector<std::string>& Option::getNames() const {
    return this->m_names;
  }

  const std::string& Option::getValue() const {
    if(!this->m_expectValue||this->m_value==""){
      throw std::runtime_error("Option must have a value");
    }
    return this->m_value;
  }

  bool Option::expectValue() const {
    return this->m_expectValue;
  }

  Option& Option::setDefaultValue(const std::string& value) {
    if(!this->m_expectValue){
      throw std::runtime_error("Option does not expect a value");
    }
    this->m_value = value;
    return *this;
  }

  Option& Option::hasValue() {
    if(!this->m_expectValue){
      this->m_expectValue = true;
    }
    return *this;
  }

  Option& Option::addAlias(const std::string& alias) {
    for(auto &it : this->m_names){
      if(it==alias){
        return *this;
      }
    }
    this->m_names.push_back(alias);
    return *this;
  }

  Option& Option::setMandatory() {
    this->m_mandatory = true;
    return *this;
  }

  bool Option::isMandatory() const {
    return this->m_mandatory;
  }

  void Option::parsed(){
    this->m_parsed = true;
  }

  bool Option::operator==(const std::string& arg) const {
    for(auto it : this->m_names){
      if(it==arg){
        return true;
      }
    }
    return false;
  }

  bool Option::operator!=(const std::string& arg) const {
    return (!this->operator==(arg));
  }

  Option& Option::operator=(const std::string& value) {
    this->m_value = value;
  }

  Option::operator bool() const {
    return this->m_parsed;
  }
}
