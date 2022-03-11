#ifndef T_TUPLE_H
#define T_TUPLE_H

namespace t {


  template<typename ... Others>
  class Tuple {
    int operator()(){
      return 0;
    }
  public:
    // template<int index>
    //  auto get() {

    //   return nullptr;
    // }

    // template <typename ... OtherTypes>
    // bool operator==(const Tuple<OtherTypes...>& other)const {
    //       return true;
    // }

  };


  template<typename T, typename ... Others>
  class Tuple<T, Others...> {
  public:
    /**
     * Default constructor
     */
    Tuple() = default;


    /**
     * Constructor to initialize values
     */
    Tuple(T firstValue, Others ... otherValues) : value(firstValue),rightMember(otherValues ...)   
    {
    }


    /**
     * Value getter
     */
    template<int index>
     const auto& get() const{
      // return rightMember.test();
      if constexpr( index != 0){
          return rightMember.template get<index - 1 >();
      }else{
        return this->value;
      }
    }

    /**
     * Value getter
     */
    template<int index>
     auto& get() {
      // return rightMember.test();
      if constexpr( index != 0){
          return rightMember.template get<index - 1 >();
      }else{
        return this->value;
      }
    }

    /**
     * Addition between to tuples
     */
    template <typename OtherType, typename ... OtherTypes>
    Tuple<T,Others ...> operator+(const Tuple<OtherType, OtherTypes...>& other)const {
      
    }

    /**
     * Addition between two tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> &operator+=(const Tuple<OtherTypes...>& other) {
      const size_t size = sizeof...(OtherTypes) ;
      this->value +=  other.value;
      if constexpr(size ==1){
        return *this;
      }else{
        this->rightMember += other.rightMember;
      }
      return *this;
    }

    /**
     * Substraction between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator-(const Tuple<OtherTypes...>& other)const {

    }

    /**
     * Substraction between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> & operator-=(const Tuple<OtherTypes...>& other) {
      const size_t size = sizeof...(OtherTypes) ;
      this->value -=  other.value;
      if constexpr(size ==1){
        return *this;
      }else{
        this->rightMember -= other.rightMember;
      }
      return *this;
    }

    /**
     * Multiplication between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator*(const Tuple<OtherTypes...>& other)const {

    }

    /**
     * Multiplication between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...>& operator*=(const Tuple<OtherTypes...>& other) {
      const size_t size = sizeof...(OtherTypes) ;
      this->value *=  other.value;
      if constexpr(size ==1){
        return *this;
      }else{
        this->rightMember *= other.rightMember;
      }
      return *this;
    }

    /**
     * Division between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator/(const Tuple<OtherTypes...>& other)const {

    }

    /**
     * Division between to tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...>& operator/=(const Tuple<OtherTypes...>& other) {
      const size_t size = sizeof...(OtherTypes) ;
      this->value /=  other.value;
      if constexpr(size ==1){
        return *this;
      }else{
        this->rightMember /= other.rightMember;
      }
      return *this;
    }

    /**
     * Comparaison operators
     */
    template <typename ... OtherTypes>
    bool operator==(const Tuple<OtherTypes...>& other)const {
      const size_t size = sizeof...(OtherTypes) ;
        if ( other.value != value){
          return false;
        }else{
            if constexpr(size == 1){
              return true;
            }else{
              return (this->rightMember == other.rightMember);
            }
        } 
    }


    template <typename ... OtherTypes>
    bool operator!=(const Tuple<OtherTypes...>& other)const {
      const size_t size = sizeof...(OtherTypes) ;

        if ( other.value != value){
          return true;
        }else{
            if constexpr(size == 1){
              return false;
            }else{
              return (this->rightMember != other.rightMember);
            }
        }

    }

    template <typename ... OtherTypes>
    bool operator<(const Tuple<OtherTypes...>& other)const {
      const size_t size = sizeof...(OtherTypes) ;

        if ( value < other.value ){
          return true;
        }else {
            if constexpr(size == 1){
              return false;

            }else{
              return (this->rightMember < other.rightMember);
            }
        } 
    }

    template <typename ... OtherTypes>
    bool operator<=(const Tuple<OtherTypes...>& other) const{
      const size_t size = sizeof...(OtherTypes) ;

        if ( value <= other.value ){
          return true;
        }else {
            if constexpr(size == 1){
              return true;
            }else{
              return (this->rightMember <= other.rightMember);
            }
        } 

    }

    template <typename ... OtherTypes>
    bool operator>(const Tuple<OtherTypes...>& other)const {
      const size_t size = sizeof...(OtherTypes) ;

        if ( value > other.value ){
          return true;
        }else {
            if constexpr(size == 1){
              return false;
            }else{
              return (this->rightMember > other.rightMember);
            }
        }
         
    }

    template <typename ... OtherTypes>
    bool operator>=(const Tuple<OtherTypes...>& other) const{
      const size_t size = sizeof...(OtherTypes) ;

        if ( value >= other.value ){
          return true;
        }else {

            if constexpr(size == 1){
              return true;
            }else{
              return (this->rightMember >= other.rightMember);
            }

        } 
    }

    /**
     * Concatenate two tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator|(Tuple<OtherTypes...>&& other) {

    }
  private:
    T value;
    t::Tuple<Others ...> rightMember;
  };

  /**
   * Helper function to create a tuple
   */
  template <class... Types>
  constexpr Tuple<Types...> makeTuple(Types&&... args) {
    return {std::forward<Types>(args)...};
  }
  

}

#endif // T_TUPLE_H
