#ifndef T_TUPLE_H
#define T_TUPLE_H

namespace t {


  bool check(){
    return true;
  }


  template<typename ... Others>
  class Tuple {

  public:


  };

    /**
   * Helper function to create a tuple
   */
  template <class... Types>
  constexpr Tuple<Types...> makeTuple(Types&&... args) {
    return {std::forward<Types>(args)...};
  }


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

    Tuple<Others ...> getRightMember()const {
      return this->rightMember;
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
    
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator+(const Tuple<OtherTypes...>& other) const {
      auto t = *this;
      t += other; 
      return t;
    }




    /**
     * Addition between two tuples - in place
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> &operator+=(const Tuple<OtherTypes...>& other) {
      const size_t size = sizeof...(OtherTypes) ;
      this->value = get<0>() +  other.template get<0>();
      if constexpr(size ==1){
        return *this;
      }else{
        this->rightMember += other.getRightMember();
      }
      return *this;
    }

    /**
     * Substraction between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator-(const Tuple<OtherTypes...>& other)const {
      auto t = *this;
      t -= other; 
      return t;
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
        this->rightMember -= other.getRightMember();;
      }
      return *this;
    }

    /**
     * Multiplication between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator*(const Tuple<OtherTypes...>& other)const {
      auto t = *this;
      t *= other; 
      return t;
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
        this->rightMember *= other.getRightMember();;
      }
      return *this;
    }

    /**
     * Division between to tuples
     */
    template <typename ... OtherTypes>
    Tuple<T,Others ...> operator/(const Tuple<OtherTypes...>& other)const {
      auto t = *this;
      t /= other; 
      return t;
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
        this->rightMember /= other.getRightMember();;
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

  // /**
  //  * Helper function to create a tuple
  //  */
  // template <class... Types>
  // constexpr Tuple<Types...> makeTuple(Types&&... args) {
  //   return {std::forward<Types>(args)...};
  // }

  

}

#endif // T_TUPLE_H
